/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 09:56:29 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 22:31:06 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"

int	main(int ac, char** av) {

	if (ac != 3) {
		std::cerr << "Usage: " << *av << " [port] [password]\n";
		return EXIT_FAILURE;
	}
	return Irc::start(av[1], av[2]);
}
