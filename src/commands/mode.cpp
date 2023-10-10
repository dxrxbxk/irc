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
#include "utils.hpp"
#include <cstddef>

Mode::Mode(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Mode::~Mode(void) {}

bool	Mode::valid_mode(char c) {
	return (c == 'i' || c == 't' || c == 'k' || c == 'o' || c =='l');
}

Command::ret_type	Mode::handle_user() {
	_conn.enqueue(RPL::u_mod_unknown_flag(_conn.info()));
	return 0;
}

Command::ret_type	Mode::handle_channel(std::string& target, std::string& mode) {
	if (not _server.channel_exist(target)) {
			_conn.enqueue(RPL::no_such_channel(_conn.info(), target));
			return 0;
	}

	Channel& channel = _server.channel(target);

	if (not channel.user_in(_conn.nickname())) { // impossible ? 
			_conn.enqueue(RPL::not_on_channel(_conn.info(), target));
			return 0;
	}
	else if (not channel.is_op(_conn.nickname())) {
			_conn.enqueue(RPL::chano_privs_needed(_conn.info(), channel.name()));
			return 0;
	}
//	param_type param = _msg.params(2);
	std::size_t _index = 2;
	for (std::size_t i = 0; i < mode.size(); i++) {
		if (mode[i] == '+') {
			std::string param = _msg.params(_index++);
			switch (mode[i + 1]) {
				case 'i':
					channel.invite_only(true);
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				case 't':
					channel.topic(true);
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				case 'k':
					if (not param.empty()) {
						channel.key(param);
						channel.key(true);
					}
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				case 'o':
					if (not channel.user_in(param)) {
						_conn.enqueue(RPL::user_not_in_channel(_conn.info(), param, channel.name()));
						break;
					}
					channel.add_op(param);
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				case 'l':
					if (param.empty()) {
						_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
						break;
					}
					channel.limit(std::atoi(param.c_str()));
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				default:
					_conn.enqueue(RPL::unknown_mode(_conn.info(), mode[i + 1]));
			}
		}
		else if (mode[i] == '-') {
			std::string param = _msg.params(_index++);
			switch (mode[i + 1]) {
				case 'i':
					channel.invite_only(false);
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				case 't':
					channel.topic(false);
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				case 'k':
					channel.key('k');
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				case 'o':
					if (not channel.user_in(param)) {
						_conn.enqueue(RPL::user_not_in_channel(_conn.info(), param, channel.name()));
						break;
					}
					channel.rm_op(param);
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				case 'l':
					channel.limit(false);
					channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), mode));
					break;
				default:
					_conn.enqueue(RPL::unknown_mode(_conn.info(), mode[i + 1]));
			}
		}
	}
	return 0;
}

Command::ret_type	Mode::execute(void) {
	std::string& target = _msg.params_first();
	std::string& modes = _msg.params(1);

	if (not _msg.has_params() || _msg.params_size() == 1) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
		return 0;
	}
	if (target[0] == '#' || target[0] == '&')
		handle_channel(target, modes);
	else
		handle_user();
	return 0;
}

Command* Mode::create(Connexion& conn, Message& msg) {
	return new Mode(conn, msg);
}
