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
#include "channel.hpp"
#include "utils.hpp"
#include <cstddef>

Mode::Mode(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Mode::~Mode(void) {}

bool	Mode::valid_mode(char c) {
	return (c == 'i' || c == 't' || c == 'k' || c == 'o' || c =='l');
}

Command::ret_type	Mode::handle_user(std::string& target, std::string& mode, std::string& param) {
	_conn.enqueue(RPL::u_mod_unknown_flag(_conn.info()));
	return 0;
}

Command::ret_type	Mode::handle_channel(std::string& target, std::string& mode, std::string& param) {
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

	for (std::size_t i = 0; i < mode.size(); i++) {
		if (mode[i] == '+') {
			if (not valid_mode(mode[i + 1])) {
				_conn.enqueue(RPL::u_mod_unknown_flag(_conn.info()));
				return 0;
			}
			switch (mode[i + 1]) {
				case 'i':
					channel.invite_only(true);
					break;
				case 't':
					channel.topic(true);
					break;
				case 'k':
					if (not param.empty()) {
						channel.key(param);
						channel.key(true);
					}
					break;
				case 'o':
					if (not channel.user_in(param)) {
						_conn.enqueue(RPL::user_not_in_channel(_conn.info(), param, channel.name()));
						return 0;
					}
					channel.add_op(param);
					channel.broadcast("MODE " + channel.name() + " +o " + param, _conn);
					break;
				case 'l':
					try {
						if (param.empty())
							_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
						channel.limit(utils::to_integer<int>(param));
					} catch (const std::exception& e) {
						Logger::info("Error" + std::string(e.what()));
					}
					break;
			}
		}
		else if (mode[i] == '-') {
			if (not valid_mode(mode[i + 1])) {
				_conn.enqueue(RPL::u_mod_unknown_flag(_conn.info()));
				return 0;
			}
			switch (mode[i + 1]) {
				case 'i':
					channel.invite_only(false);
					break;
				case 't':
					channel.topic(false);
					break;
				case 'k':
					channel.key('k');
					break;
				case 'o':
					channel.rm_op(param);
					break;
				case 'l':
					channel.limit(false);
					break;
			}
		}
	}
	return 0;
}

Command::ret_type	Mode::execute(void) {
	std::string& target = _msg.params_first();
	std::string& mode = _msg.param(1);
	std::string& param = _msg.param(2);

	if (not _msg.has_params() || _msg.params_size() == 1) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
		return 0;
	}
	if (target[0] == '#' || target[0] == '&')
		handle_channel(target, mode, param);
	else
		handle_user(target, mode, param);

	return 0;
}

Command* Mode::create(Connexion& conn, Message& msg) {
	return new Mode(conn, msg);
}
