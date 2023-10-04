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

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Nick::Nick(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Nick::~Nick(void) {}


void Nick::execute(void) {
	if (not _msg.has_params()) {
		_conn.enqueue(RPL::no_nickname_given(_conn.info()));
		return;
	}

	std::string& first = _msg.params_first();
	if (_server.nick_exist(first)) {

		_conn.enqueue(RPL::nickname_in_use(_conn.info(), first));

		if (not _conn.registered())
			_conn.disconnect();


		return ;
	}

	_conn.nickname(first);

	if (_conn.registered()) {
		_server.ch_nick(_conn.nickname(), first);
	}

	else { _server.accept_newcomer(_conn); }

	return ;
}


Command* Nick::create(Connexion& conn, Message& msg) {
	return new Nick(conn, msg);
}
