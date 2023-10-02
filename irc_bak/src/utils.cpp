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

void	closeFd(int fd) {
	if (fd > 2) {
		std::cout << "Closing " << fd << std::endl;
		if (close(fd) == -1)
			std::cerr << "Error: close: " << strerror(errno) << std::endl;
	}
}

std::string custom_inet_ntoa(struct in_addr addr) {
    std::string ip_str;
    for (int i = 0; i < 4; ++i) {
        ip_str += intToString((addr.s_addr >> (i * 8)) & 0xFF);
        if (i < 3) {
            ip_str += ".";
        }
    }
    return ip_str;
}

std::string intToString(int num) {
	std::ostringstream oss;
	oss << num;
	return oss.str();
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
