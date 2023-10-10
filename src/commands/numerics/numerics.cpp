/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numerics.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:22:36 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 02:26:54 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connexion.hpp"
#include "server.hpp"
#include "numerics.hpp"
#include <sstream>

#define CRLF "\r\n"

RPL::ret_type	RPL::inviting(arg_type info, const std::string& nick, const std::string& channel) {
	std::stringstream	buffer;
	buffer << "341 " << info.nickname << " " << nick << " " << channel << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::user_on_channel(arg_type info, const std::string& channel, const std::string& user) {
	std::stringstream	buffer;
	buffer << "353 " << info.nickname << " = " << channel << " :" << user << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::channel_mode_is(arg_type info, const std::string& channel, const std::string& mode) {
	std::stringstream	buffer;
	buffer << "324 " << info.nickname << " " << channel << " " << mode << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::unknown_mode(arg_type info, const char c) {
	std::stringstream	buffer;
	buffer << "472 " << info.nickname << " " << c << " :is unknown mode char to me" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::welcome(arg_type info) {
	std::stringstream	buffer;
	buffer << "001 " << info.nickname << " :Welcome to the IRC server "
		<< info.nickname << "!" << info.username << "@" << info.hostname << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::topic(arg_type info, const std::string& channel, const std::string& topic) {
	std::stringstream	buffer;
	buffer << "332 " << info.nickname << " " << channel << " " << topic << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::no_topic(arg_type info, const std::string& channel) {
	std::stringstream	buffer;
	buffer << "331 " << info.nickname << " " << channel << " :No topic is set" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::user_not_in_channel(arg_type info, const std::string& nick, const std::string& channel) {
	std::stringstream	buffer;
	buffer << "441 " << info.nickname << " " << nick << " " << channel << " :They aren't on that channel" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::channel_is_full(arg_type info, const std::string& channel) {
	std::stringstream	buffer;
	buffer << "471 " << info.nickname << " " << channel << " :Cannot join channel (+l)" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::chano_privs_needed(arg_type info, const std::string& channel) {
	std::stringstream	buffer;
	buffer << "482 " << info.nickname << " " << channel << " :You're not channel operator" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::no_such_channel(arg_type info, const std::string& channel) {
	std::stringstream	buffer;
	buffer << "403 " << info.nickname << " " << channel << " :No such channel" << CRLF;
	return buffer.str();
}

RPL::ret_type RPL::not_on_channel(arg_type info, const std::string& channel) {
	std::stringstream	buffer;
	buffer << "442 " << info.nickname << " " << channel << " :You're not on that channel" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::no_such_nick(arg_type info, const std::string& nickname) {
	std::stringstream	buffer;
	buffer << "401 " << info.nickname << " " << nickname << " :No suck nick/channel" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::passwd_mismatch(arg_type info) {
	std::stringstream	buffer;
	if (not info.nickname.empty())
		buffer << "464 " << info.nickname << " :Password incorrect" << CRLF;
	else
		buffer << "464 nick_name_not_set :Password incorrect" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::already_registered(arg_type info) {
	std::stringstream	buffer;
	buffer << "462 " << info.nickname << " :You may not reregister" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::erroneus_nickname(arg_type info, const std::string& nick) {
	std::stringstream	buffer;
	buffer << "432 " << info.nickname << " " << nick << " :Erroneus nickname" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::nickname_in_use(arg_type info, const std::string& nick) {
	std::stringstream	buffer;
	buffer << "433 " << nick << " :Nickname in use" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::need_more_params(arg_type info, const std::string& cmd) {
	std::stringstream	buffer;
	buffer << "461 " << info.nickname << " " 
		<< cmd << " :Need more params" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::motd_start(arg_type info) {
	std::stringstream	buffer;
	buffer << "375 " << info.nickname << " :- " << info.nickname << " Message of the day - " << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::motd(arg_type info, const std::string& msg) {
	std::stringstream	buffer;
	buffer << "372 " << info.nickname << " :- " << msg << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::end_of_motd(arg_type info){
	std::stringstream	buffer;
	buffer << "376 " << info.nickname << " :End of /MOTD command" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::no_nickname_given(arg_type info) {
	std::stringstream	buffer;
	buffer << "431 " << info.nickname << " :No nickname given" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::u_mod_unknown_flag(arg_type info) {
	std::stringstream	buffer;
	buffer << "501 " << info.nickname << " :Cannot set user mode" << CRLF;
	return buffer.str();
}
