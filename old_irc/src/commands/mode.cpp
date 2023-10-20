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

void	Mode::add_mode(const char* mode, Channel &channel) {
	std::string added_mode;
	std::string param = "";
	std::size_t i = 2;
	const std::size_t p_len = _msg.params_size();
	while (*mode) {
		if (i < p_len)
			param = _msg.params(i);
		switch (*mode) {
			case 'i':
				channel.invite_only(true);
				added_mode += *mode;
				break;
			case 't':
				channel.topic(true);
				added_mode += *mode;
				break;
			case 'k':
				if (param.empty()) {
					_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
					break;
				}
				else if (not channel.key().empty()) {
					_conn.enqueue(RPL::key_set(_conn.info(), channel.name()));
					break ;
				}
				channel.key(param);
				added_mode += *mode;
				i < p_len ? i++ : i;
				break;
			case 'o':
				if (param.empty()) {
					_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
					break;
				}
				else if (not channel.user_in(param)) {
					_conn.enqueue(RPL::user_not_in_channel(_conn.info(), param, channel.name()));
					break;
				}
				channel.add_op(param);
				added_mode += *mode;
				i < p_len ? i++ : i;
				break;
			case 'l':
				if (param.empty()) {
					_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
					break;
				}
				channel.limit(std::atoi(param.c_str()));
				added_mode += *mode;
				i < p_len ? i++ : i;
				break;
			default:
				_conn.enqueue(RPL::unknown_mode(_conn.info(), *mode));
		}
		mode++;
	}
	if (not added_mode.empty())
		channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), "+" + added_mode));
}

void	Mode::remove_mode(const char* mode, Channel& channel) {
	std::string added_mode;
	std::string param = "";
	std::size_t i = 2;
	const std::size_t p_len = _msg.params_size();
	while (*mode) {
		if (i < p_len)
			param = _msg.params(i);
		switch (*mode) {
			case 'i':
				channel.invite_only(false);
				added_mode += *mode;
				break;
			case 't':
				channel.topic(false);
				added_mode += *mode;
				break;
			case 'k':
				channel.key("");
				added_mode += *mode;
				break;
			case 'o':
				if (not channel.user_in(param)) {
					_conn.enqueue(RPL::user_not_in_channel(_conn.info(), param, channel.name()));
					break;
				}
				i < p_len ? i++ : i;
				channel.rm_op(param);
				added_mode += *mode;
				break;
			case 'l':
				channel.limit(false);
				added_mode += *mode;
				break;
			default:
				_conn.enqueue(RPL::unknown_mode(_conn.info(), *mode));
		}
		mode++;
	}
	if (not added_mode.empty())
		channel.broadcast(RPL::channel_mode_is(_conn.info(), channel.name(), "-" + added_mode));
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

	for (std::size_t i = 0; i < mode.size(); i++) {
		if (mode[i] == '+') {
			add_mode(mode.c_str() + i, channel);
			return 0;
		}
		else if (mode[i] == '-') {
			remove_mode(mode.c_str() + i, channel);
			return 0;
		}
	}
	return 0;
}

Command::ret_type	Mode::execute(void) {

	if (not _msg.has_params() || _msg.params_size() == 1) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
		return 0;
	}

	std::string& target = _msg.params_first();
	std::string& modes = _msg.params(1);

	if (target[0] == '#' || target[0] == '&')
		handle_channel(target, modes);
	else
		handle_user();
	return 0;
}

Command* Mode::create(Connexion& conn, Message& msg) {
	return new Mode(conn, msg);
}
