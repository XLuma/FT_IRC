/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <hbanthiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 19:55:13 by hbanthiy          #+#    #+#             */
/*   Updated: 2022/08/15 21:17:28 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <exception>
# include <poll.h> // Have a lot of common includes make a master header later 
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <list>
#include "Client.hpp"

#define PORT 	6667
class Client;
class Server
{

	public:

		Server(unsigned int port, std::string paswd);
		Server( Server const & src );
		~Server();

		Server &		operator=( Server const & rhs );

	// Getters 



	// Setters 

	private:
	
	unsigned int		port; 
	unsigned int 		total_client_count;
	
	
	pollfd				p_fd;
	struct sockaddr_in6 addr_info;
	std::string 		passwrd;
	std::string 		server_ip_addr;
	std::list<Client> 	list_of_all_clients;

	
	// channel list 
	// Operator list
	// command map 
	// reply map 

	// Exceptions 
	class SocketFailException : public std::exception
	{
		public: virtual const char* what() const throw();
	};

	class SetsockoptFailException : public std::exception
	{
		public: virtual const char* what() const throw();
	};
	
	class BindFailException : public std::exception
	{
		public: virtual const char* what() const throw();
	};
	
	class ListenFailException : public std::exception
	{
		public: virtual const char* what() const throw();
	};
};

#endif