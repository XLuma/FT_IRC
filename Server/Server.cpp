/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrecq <olabrecq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:49:01 by olabrecq          #+#    #+#             */
/*   Updated: 2022/08/14 14:31:02 by olabrecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"


//===== CONSTRUCTOR & DESTRUCTOR =======
Server::Server( const char* IP, const char* port, std::string passW )
{
	_port = port;
	_listener = 0;
	_addrlen = 0;
}


Server::~Server()
{
	
}

//======== START, ACCEPT, BIND, LISTEN, ===========

void Server::start( void ) 
{
	_listener = get_listener_socket();
	if(_listener == -1)
		throw CreateSocketError();
	std::cout << GREEN << "Socket created successfully \n" << RESET;
	accept_client();
}

int     Server::get_listener_socket(void)
{
    int     listener;  // listening socket descriptor 
    int     opt = 1;  
    int     ret;

    struct addrinfo    hints, *ai, *p;

    // Lets get us a socket and bind to it
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((ret = getaddrinfo(NULL, _port, &hints, &ai)) != 0)
    {
        std::cerr << "Select Server: " << gai_strerror(ret) << '\n';
        exit(1);
    }

    for(p = ai; p != NULL; p = p->ai_next)
    {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0)
            continue ;
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener);
            continue ;
        }
        break ;
    }

    freeaddrinfo(ai);
    
    // if we got here without binding throw exception 
    if (p == NULL)
        throw BindingError();
    
    // Start Listening 
    if (listen(listener, 10) == -1)
        return (-1);
    
    return (listener);
}

int Server::accept_client( void )
{
	// Lets start with 5 client connections 
    int fd_count = 0;
    int fd_size = 5;
    struct pollfd *pfds = new pollfd[(sizeof(*pfds) * fd_size)];
	
	  // Add listener to set
    pfds[0].fd = _listener;
    pfds[0].events = POLLIN;

    fd_count = 1; // For the listener

    // main loop
    for(;;)
    {
        int poll_count = poll(pfds, fd_count, -1);
		
        if (poll_count == -1)
        {
            std::cerr << "Poll Error\n";
            exit(1);
        }

        // Run through existing connections looking for data
        for (int i = 0; i < fd_count; i++)
        {
            if (pfds[i].revents & POLLIN)
            {
				
                if (pfds[i].fd == _listener)
                {
                    // if listener is ready to read, handle new
                    _addrlen = sizeof (_client_addr);
                    _new_fd = accept(_listener, (struct sockaddr *)&_client_addr, &_addrlen);
                    if (_new_fd == -1)
                        std::cerr << "Accept error \n";
                    else 
                    {
                        add_to_pfds(&pfds, _new_fd, &fd_count, &fd_size);
                        std::cout << "Poll Server: new connection from" << inet_ntop(_client_addr.ss_family, get_in_addr((struct sockaddr *)&_client_addr), _remoteIP, INET6_ADDRSTRLEN) << " " << _new_fd;
                    }
                }
                else 
                {
                    // if not the listener, we're just a regular client 
                    int nbytes = recv(pfds[i].fd, _buff, sizeof(_buff), 0);
					
					//! Irssi: Not connected to server when i pass command ??
					printf("command : %s\n", _buff);

					
                    int sender_fd = pfds[i].fd;
					

                    if (nbytes <= 0)
                    {
                        // error or connection closed by client
                        if (nbytes == 0)
                        {
                            // connection closed
                            std::cout << "Poll Server: socket " << sender_fd << " disconnected!\n";
                        }
                        else
                        {
                            std::cout << "Server Recv Error\n";
                        }

                        close(pfds[i].fd);
                        del_from_pfds(pfds, i, &fd_count);
                    }
                    else 
                    {
                        // We have data from a client
                        for(int j = 0; j < fd_count; j++)
                        {
                            // Send to everyone
                            int dest_fd = pfds[j].fd;
                            // Except the listener and ourselves
                            if (dest_fd != _listener && dest_fd != sender_fd)
							{
                                if (send(dest_fd, _buff, nbytes, 0) == -1)
                                    std::cerr << "Poll Server : Send failed\n";
                            }  
                        }
                    }
                }
            }
        }
    }
}

// Add new socket fds to set of poll 

void    Server::add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size)
{
    // Create a dynamically expanding array to add more pfds
    if (*fd_count == *fd_size)
    {
        *fd_size *= 2;
        *pfds = (pollfd *)realloc(*pfds, sizeof(**pfds) * (*fd_size));
    }
    (*pfds)[*fd_count].fd = newfd;
    (*pfds)[*fd_count].events = POLLIN; // check ready to read
    (*fd_count)++;
}

// Remove an index from the fd set

void    Server::del_from_pfds(struct pollfd pfds[], int i, int *fd_count)
{
    // Copy the one from the end over this one
    pfds[i] = pfds[*fd_count - 1];
    (*fd_count)--;
}

// get sockaddr, Ipv4 or Ipv6
void   *get_in_addr(struct sockaddr *s)
{
    if (s->sa_family == AF_INET)
        return &(((struct sockaddr_in *)s)->sin_addr);
        
    return &(((struct sockaddr_in6 *)s)->sin6_addr);   
}