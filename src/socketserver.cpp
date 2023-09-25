/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketserver.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:59:12 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/25 21:54:17 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socketserver.hpp"

Socketserver::Socketserver(std::map<int, Connexion>& m_ref, Poll &p_ref, int fd) 
: sock_fd(fd), m_conns(&m_ref), poller(&p_ref) {
	std::cout << "Socketserver constructor called" << std::endl;
}

Socketserver::~Socketserver() {
	std::cout << "Socketserver destructor called" << std::endl;
}

void	Socketserver::notify(void) {
	int cfd;

	std::cout << "\nSending notification" << std::endl;
	cfd = accept(sock_fd, NULL, NULL);
	if (cfd == -1) {
		ERROR(handleSysError("accept"));
	} else {
		std::cout << "Connexion fd created: " << cfd << std::endl;
		(*m_conns)[cfd] = Connexion(cfd, *m_conns);
		poller->addEvent((*m_conns)[cfd]);
	}
}

int		Socketserver::getFd(void) {
	return sock_fd;
}

void	Socketserver::disconnect(void) {
	std::cout << "Socketserver::disconnect" << std::endl;
}

Socketserver::Socketserver(const Socketserver& copy) 
: sock_fd(copy.sock_fd), m_conns(copy.m_conns), poller(copy.poller) {
}

Socketserver& Socketserver::operator=(const Socketserver& copy) {
	if (this != &copy) {
		sock_fd = copy.sock_fd;
		m_conns = copy.m_conns;
		poller = copy.poller;
	}
	return *this;
}
