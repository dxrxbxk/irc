/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:04:16 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:07:08 by diroyer          ###   ########.fr       */
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
}

bool	Mode::valid_mode(char c) {
	return (c == 'i' || c == 't' || c == 'k' || c == 'o' || c =='l');
}

SendInfo	Mode::execute(void) {
	SendInfo	send_info;
	//_server.response(_conn, "");
	if (_msg.get_middle().size() == 2)
		user_mode();

	return send_info;
}

Command* Mode::create(Connexion& conn, Message& msg) {
	return new Mode(conn, msg);
}
