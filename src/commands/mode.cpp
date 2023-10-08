/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:16 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 04:03:30 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mode.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Mode::Mode(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Mode::~Mode(void) {}

bool	Mode::valid_mode(char c) {
	return (c == 'i' || c == 't' || c == 'k' || c == 'o' || c =='l');
}

Command::ret_type	Mode::execute(void) {
	if (_msg.params_size() < 2)
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
	if (_msg.params_size() == 2)
		_conn.enqueue(RPL::u_mod_unknown_flag(_conn.info()));
	return 0;
}

Command* Mode::create(Connexion& conn, Message& msg) {
	return new Mode(conn, msg);
}
