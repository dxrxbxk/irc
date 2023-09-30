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

#include "server.hpp"

Server::Server(const ServerInfo& info, const int fd, Signal& sig)
: s_info(info), sock_fd(fd), m_conns(), poller() {
	std::cout << "Socketserver constructor called" << std::endl;
	poller.addEvent(*this);
	poller.addEvent(sig);
	poller.run();
}

Server::Server(const Server& copy)
: sock_fd(copy.sock_fd), m_conns(copy.m_conns), poller(copy.poller) {
}

Server::~Server(void) {
	std::cout << "Socketserver destructor called" << std::endl;
}

void	Server::notify(void) {
	int cfd;

	std::cout << "\nSending notification" << std::endl;
	cfd = accept(sock_fd, NULL, NULL);
	if (cfd == -1) {
		ERROR(handleSysError("accept"));
	} else {
		std::cout << "Connexion fd created: " << cfd << std::endl;
		// (m_conns)[cfd] = Connexion(cfd, m_conns);
		(m_conns)[cfd] = Connexion(cfd, *this);
		poller.addEvent((m_conns)[cfd]);
	}
}

void Server::unmapConnexion(const Connexion& conn) {
	m_conns.erase(conn.getFd());
}

int		Server::getFd(void) const {
	return sock_fd;
}

void	Server::disconnect(void) {
	std::cout << "Socketserver::disconnect" << std::endl;
}


Server& Server::operator=(const Server& copy) {
	if (this != &copy) {
		sock_fd = copy.sock_fd;
		m_conns = copy.m_conns;
		poller = copy.poller;
	}
	return *this;
}
