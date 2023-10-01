/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:16 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 00:03:47 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mode.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Mode::Mode(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Mode::~Mode(void) {}

void	Mode::user_mode(void) {
	// maybe check if user is registered;
	_server.response(_conn, ERR::u_mod_unknown_flag(_conn.get_client_info()));
}

bool	Mode::valid_mode(char c) {
	return (c == 'i' || c == 't' || c == 'k' || c == 'o' || c =='l');
}

bool Mode::evaluate(void) {
	// example:
	if (not _msg.has_params())
		return false;
	return true;
}

void Mode::execute(void) {
	//_server.response(_conn, "");
	if (_msg.get_middle().size() == 2)
		user_mode();
}

Command* Mode::create(Connexion& conn, Message& msg) {
	return new Mode(conn, msg);
}
