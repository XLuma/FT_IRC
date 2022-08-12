/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olabrecq <olabrecq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:46:28 by olabrecq          #+#    #+#             */
/*   Updated: 2022/08/12 12:29:36 by olabrecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"

int main ( int ac, char ** av )
{
	(void)av;
	if ( ac != 3 ) {
		std::cout << RED << "The program should be run as follows : ./ircserv <port> <password>" << RESET << std::endl;
		return (1);
	}
	
	return (0);
}