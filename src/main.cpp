/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:56:29 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/20 23:06:22 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.hpp"

int		g_signalPipe[2];

int	main(int argc, char *argv[]) {
	if (argc < 2) {
		(void)argc;
		(void)argv;

		Irc app;
		app.run();
	} else
		std::cerr << "Usage: ./webserv [configuration file]" << std::endl;
	return (0);
}
