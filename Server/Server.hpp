/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrecq <olabrecq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:46:38 by olabrecq          #+#    #+#             */
/*   Updated: 2022/08/12 14:10:00 by olabrecq         ###   ########.fr       */
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

# define BLUE "\033[0;36m"
# define PINK "\033[0;35m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define RED "\033[0;31m"
# define RESET "\033[0m"


#ifndef PORT_N
	#define PORT_N  5000
#endif

#pragma once

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
               sa_family_t     sin6_family;   /* AF_INET6 */
               in_port_t       sin6_port;     /* port number */
               uint32_t        sin6_flowinfo; /* IPv6 flow information */
               struct in6_addr sin6_addr;     /* IPv6 address */
               uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */
           };

           struct in6_addr {
               unsigned char   s6_addr[16];   /* IPv6 address */
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


class Server
{
	private:
		struct sockaddr_in {
			short       sin_family; // family
			u_short     sin_port;  //  port 
			struct      in_addr sin_addr;  //machine address / IP address
			char        sin_zero[8]; //  special array needs to be initialised to zero 
		}
		struct sockaddr_in serv = 
		{
			.sin_family;// = AF_INET,
			.sin_addr.s_addr;// = INADDR_ANY,
			.sin_port;// = htons(PORT_N)
		};


		
	public:
		Server( void );
		Server(/* args */);
		Server(/* args */);
		~Server( void );
};

