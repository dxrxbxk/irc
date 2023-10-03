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

int	main(int ac, char** av) {

	if (ac != 3) {
		std::cerr << "Usage: " << *av << " [port] [password]\n";
		return EXIT_FAILURE;
	}
	return Irc::start(av[1], av[2]);
}
