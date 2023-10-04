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

RPL::ret_type	RPL::nickname_in_use(RPL::arg_type info, std::string& nick_used) {
	std::stringstream	buffer;
	buffer << "433 " << info.nickname << " " << nick_used
		<< " :Nickname in use" << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::welcome(arg_type info) {
	std::stringstream	buffer;
	buffer << "001 " << info.nickname << " :Welcome to the IRC server "
		<< info.nickname << "!" << info.username << "@" << info.hostname << CRLF;
	return buffer.str();
}

RPL::ret_type	RPL::end_of_motd(arg_type info){
	std::stringstream	buffer;
	buffer << "376 " << info.nickname << " :End of MOTD" << CRLF;
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
