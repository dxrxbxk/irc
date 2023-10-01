/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 01:54:20 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/01 23:31:40 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

User::User(Connexion& conn, Message& msg)
: Command(conn, msg) {}

User::~User(void) {}

bool User::evaluate(void) {
	Logger::info("evaluate");
	if (_msg.get_middle_size() != 3)
		return false;
	if (not _msg.has_trailing())
		return false;
	// example:
	return true;
}

void	User::add_user(void) {
	ClientInfo&	info = _conn.get_client_info();
	info.username.swap(_msg.get_middle(USERNAME));
	info.hostname.swap(_msg.get_middle(HOSTNAME));
	info.servername.swap(_msg.get_middle(SERVERNAME));
	info.realname.swap(_msg.get_trailing());
}

void User::execute(void) {
	//std::cout << "registered " << _conn.registered() << std::endl;
	if (not _conn.registered()) {
		PRINT("HELLO");

		_conn.set_register();
		add_user();
		_server.response(_conn, RPL::welcome(_conn.get_client_info()));
		_server.response(_conn, RPL::end_of_motd(_conn.get_client_info()));
	}
}

Command* User::create(Connexion& conn, Message& msg) {
	return new User(conn, msg);
}
