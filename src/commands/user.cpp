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

User::User(Connexion& conn, Message& msg)
: Command(conn, msg) {}

User::~User(void) {}

void	User::add_user(ClientInfo& info) {
	info.username.  swap(_msg.params(USERNAME));
	info.hostname.  swap(_msg.params(HOSTNAME));
	info.realname.  swap(_msg.trailing());
}

Command::ret_type User::execute(void) {
	if (_msg.params_size() != 3 || not _msg.has_trailing()) {
		// need reply numeric error
		return -1; }

	if (_conn.registered()) {
		Logger::debug("User: already \x1b[32mregistered\x1b[0m");
		return -1;
	}

	ClientInfo&	info = _conn.info();

	_server.accept_newcomer(_conn);

	_conn.login();
	add_user(info);
	_conn.enqueue(RPL::welcome(info));
	_conn.enqueue(RPL::motd_start(info));
	_conn.enqueue(RPL::motd(info, _server.motd()));
	_conn.enqueue(RPL::end_of_motd(info));
	return 0;
}

Command* User::create(Connexion& conn, Message& msg) {
	return new User(conn, msg);
}
