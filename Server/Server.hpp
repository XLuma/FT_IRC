/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrecq <olabrecq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:46:38 by olabrecq          #+#    #+#             */
/*   Updated: 2022/08/13 14:52:21 by olabrecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sstream>
#include <poll.h>

# define BLUE "\033[0;36m"
# define PINK "\033[0;35m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RED "\033[0;31m"
# define RESET "\033[0m"


// #define std::string string;

#ifndef PORT_N
	#define PORT_N  5000
#endif

#pragma once



class Server
{
	private:
		struct sockaddr_storage 	_client_addr;
		socklen_t 					_addrlen;
		int 						_listener;
		int 						_new_fd;
		char                        _buff[256];
    	char                        _remoteIP[INET6_ADDRSTRLEN];
		const char* 				_port;


		
	public:
		Server( const char* IP, const char * port, std::string passW );
		~Server( void );


		void start( void );
		int get_listener_socket( void );
		int accept_client ( void );
	// get sockaddr, Ipv4 or Ipv6

		void del_from_pfds(struct pollfd pfds[], int i, int *fd_count);
		void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size);
		
		class CreateSocketError : public std::exception
		{
			virtual const char* what() const throw() { return "Not able to create socket"; }
		};
		class BindingError : public std::exception
		{
			virtual const char* what() const throw() { return "Binding Failed"; }
		};
		
};
void    *get_in_addr(struct sockaddr *s);


//? https://illumos.org/man/3SOCKET/sockaddr_storage



/* NOTE
		IPv4 struct
	struct sockaddr_in {
			short       sin_family; // family
			u_short     sin_port;  //  port 
			struct      in_addr sin_addr;  //machine address / IP address
			char        sin_zero[8]; //  special array needs to be initialised to zero 
		}
		https://man7.org/linux/man-pages/man7/ip.7.html
		
		IPv6 struct
		struct sockaddr_in6 {
               sa_family_t     sin6_family;   // AF_INET6 
               in_port_t       sin6_port;     // port number 
               uint32_t        sin6_flowinfo; // IPv6 flow information 
               struct in6_addr sin6_addr;     // IPv6 address 
               uint32_t        sin6_scope_id; // Scope ID (new in 2.4) 
           };

           struct in6_addr {
               unsigned char   s6_addr[16];   // IPv6 address 
           };
			https://man7.org/linux/man-pages/man7/ipv6.7.html
			
			
		struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
           };
		   https://man7.org/linux/man-pages/man3/getaddrinfo.3.html
*/