/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 01:37:07 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 04:01:20 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nick.hpp"
#include "server.hpp"
# define NICKNAME 0

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Nick::Nick(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Nick::~Nick(void) {}


void Nick::execute(void) {
	if (_msg.params_size() != 1) {
		// need reply numeric error
		return; }

	_conn.nickname(_msg.param(NICKNAME));
}


Command* Nick::create(Connexion& conn, Message& msg) {
	return new Nick(conn, msg);
}
