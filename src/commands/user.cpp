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
	if (!(_conn.tracker() & PASS)) {
	//	_conn.enqueue(RPL::passwd_mismatch(_conn.info()));
		return -1;
	}
	if (_msg.params_size() != 3 || not _msg.has_trailing()) {
		return 0;
	}

	if (_conn.registered()) {
		_conn.enqueue(RPL::already_registered(_conn.info()));
		return 0;
	}

	ClientInfo&	info = _conn.info();

	add_user(info);
	_conn.tracker(USER);
	if (_conn.can_register() && not _conn.registered()) {
		_conn.login();
	}

	return 0;
}

Command* User::create(Connexion& conn, Message& msg) {
	return new User(conn, msg);
}
