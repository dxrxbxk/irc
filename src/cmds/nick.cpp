/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 01:37:07 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:07:22 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nick.hpp"
#include "server.hpp"
# define NICKNAME 0

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Nick::Nick(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Nick::~Nick(void) {}

void	Nick::add_nick(void) {
	ClientInfo&	info = _conn.get_client_info();
	info.nickname.swap(_msg.get_middle(NICKNAME));
}

SendInfo Nick::execute(void) {
	SendInfo	send_info;
	//_server.response(_conn, "");
	add_nick();
	return send_info;
}

Command* Nick::create(Connexion& conn, Message& msg) {
	return new Nick(conn, msg);
}
