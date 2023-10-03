/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 00:38:28 by diroyer           #+#    #+#             */
/*   Updated: 2023/09/25 14:48:37 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"


std::string custom_inet_ntoa(struct in_addr addr) {
    std::string ip_str;
    for (int i = 0; i < 4; ++i) {
        ip_str += to_string((addr.s_addr >> (i * 8)) & 0xFF);
        if (i < 3) {
            ip_str += ".";
        }
    }
    return ip_str;
}

void setnonblocking(const int socket) {
    int opts;
    if ((opts = ::fcntl(socket, F_GETFL)) < 0)
		throw std::runtime_error("GETFL failed");
    opts = opts | O_NONBLOCK;
    if (::fcntl(socket, F_SETFL, opts) < 0)
		throw std::runtime_error("SETFL failed");
}

std::string	handleGaiError(int errcode) {
	std::ostringstream errorMsgStream;
	errorMsgStream << "Error: getaddrinfo: " <<  gai_strerror(errcode) << std::endl;
	return errorMsgStream.str();
}

std::string	handleSysError(const std::string& syscall) {
	std::ostringstream errorMsgStream;
	errorMsgStream << "Error: " << syscall << ": " << strerror(errno);
	return errorMsgStream.str();
}
