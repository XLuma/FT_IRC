/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrecq <olabrecq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:46:28 by olabrecq          #+#    #+#             */
/*   Updated: 2022/08/13 14:38:39 by olabrecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"

// echo -n "whatever" | nc "127.0.0.1" 5000

int main ( int ac, char ** av )
{
	if ( ac != 3 ) {
		std::cerr << RED << "The program should be run as follows : ./ircserv <port> <password>" << RESET << std::endl;
		return (-1);
	}
	Server* serv = new Server("127.0.0.1", av[1], av[2]);

	serv->start();

	delete serv;

	
	
	return (0);
}