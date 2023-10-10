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
#include "numerics.hpp"
#include "server.hpp"
#include "utils.hpp"

Nick::Nick(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Nick::~Nick(void) {}

Command::ret_type Nick::execute(void) {
	std::string& first = _msg.params_first();
	int nb_guest = 1;

	if (!(_conn.tracker() & PASS)) { //hein ?
		_conn.enqueue(RPL::passwd_mismatch(_conn.info()));
		return -1;
	}

	if (not _msg.has_params()) {
		_conn.enqueue(RPL::no_nickname_given(_conn.info()));
		return 0;
	}

	if (first.size() > 9 || first[0] == '#' || first[0] == '&') {
		_conn.enqueue(RPL::erroneus_nickname(_conn.info(), first));
		return 0;
	}

	if (_server.nick_exist(first)) {

		if (not _conn.registered()) {
			_conn.tracker(NICK);
			_conn.nickname("Guest" + utils::to_string(nb_guest));
			nb_guest++;
			if (nb_guest > 999)
				return -1;
			return 0;
		}
		_conn.enqueue(RPL::nickname_in_use(_conn.info(), first));
		return 0;
	}

	if (_conn.registered()) {
		_server.broadcast(":" + _conn.nickname() + " NICK " + first + CRLF);
		_server.ch_nick(_conn, first);
	}
	else {
		_conn.nickname(first);
		_conn.tracker(NICK);
	}
	return 0;
}

Command* Nick::create(Connexion& conn, Message& msg) {
	return new Nick(conn, msg);
}
