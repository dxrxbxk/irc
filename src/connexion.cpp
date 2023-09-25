/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:41:30 by diroyer           #+#    #+#             */
/*   Updated: 2023/09/25 14:47:04 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "connexion.hpp"
#define BUFFER_SIZE 1024

Connexion::Connexion() : sock_fd(-1), buffer(), m_ptr(NULL) {
	//std::cout << "Connexion default constructor called" << std::endl;
}

Connexion::~Connexion() {
	//std::cout << "Connexion destructor called : " << sock_fd << std::endl;
}

Connexion::Connexion(int fd, std::map<int, Connexion> &ref) 
: sock_fd(fd), buffer(), m_ptr(&ref) {
	//std::cout << "Connexion fd constructor called, fd = " << fd << std::endl;
}

void	Connexion::disconnect(void) {
	if (m_ptr)
		m_ptr->erase(sock_fd);
	std::cout << "Connexion::disconnect" << std::endl;
}

void	Connexion::setFd(int fd) {
	sock_fd = fd;
}

int		Connexion::getFd(void) {
	return sock_fd;
}

void	Connexion::notify(void) {
	char		rec_buf[BUFFER_SIZE + 1];
	ssize_t		rec_len;
	std::string ret_buf;
	std::string send_buf;
 
	rec_len = recv(sock_fd, rec_buf, BUFFER_SIZE, 0);
	if (rec_len == -1)
		ERROR(handleSysError("recv"));
	else {
		rec_buf[rec_len] = '\0';
		send_buf = "Hello";
		
		if (send(this->sock_fd, send_buf.c_str(), send_buf.size(), 0) == -1)
			ERROR(handleSysError("send"));
	}
}

Connexion::Connexion(const Connexion &copy) {
	*this = copy;
}

Connexion& Connexion::operator=(const Connexion &copy) {
	if (this != &copy) {
		sock_fd = copy.sock_fd;
		buffer = copy.buffer;
		m_ptr = copy.m_ptr;
	}
	return *this;
}
