/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 01:37:07 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/01 18:48:21 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nick.hpp"
#include "server.hpp"
# define NICKNAME 0

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Nick::Nick(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Nick::~Nick(void) {}

bool Nick::evaluate(void) {

	// example:
	if (not _msg.has_params())
		return false;
	// check si ya plusieurs middle;
	return true;
}

void	Nick::add_nick(void) {
	ClientInfo&	info = _conn.get_client_info();
	info.nickname.swap(_msg.get_middle(NICKNAME));
}

void Nick::execute(void) {
	//_server.response(_conn, "");
	add_nick();
}

Command* Nick::create(Connexion& conn, Message& msg) {
	return new Nick(conn, msg);
}
