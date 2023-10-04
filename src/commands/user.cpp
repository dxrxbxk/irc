/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 01:54:20 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 04:00:01 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "user.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

User::User(Connexion& conn, Message& msg)
: Command(conn, msg) {}

User::~User(void) {}

void	User::add_user(void) {
	ClientInfo&	info = _conn.info();
	info.username.  swap(_msg.param(USERNAME));
	info.hostname.  swap(_msg.param(HOSTNAME));
	info.realname.  swap(_msg.trailing());
}

void User::execute(void) {

	PRINT("HELLO");
	if (_msg.params_size() != 3 || not _msg.has_trailing()) {
		// need reply numeric error
		return; }

	if (_conn.registered()) {
		Logger::debug("User: already \x1b[32mregistered\x1b[0m");
		return;
	}

	ClientInfo&	info = _conn.info();

	_server.accept_newcomer(_conn);

	_conn.login();
	add_user();
	_conn.enqueue(RPL::welcome(info));
	_conn.enqueue(RPL::end_of_motd(info));
	return;
}

Command* User::create(Connexion& conn, Message& msg) {
	return new User(conn, msg);
}
