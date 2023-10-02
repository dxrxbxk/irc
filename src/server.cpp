/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:59:12 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 02:10:44 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

Server::Server(const ServerInfo& info, const int fd, Signal& sig)
: s_info(info), sock_fd(fd), m_conns(), poller(*this), _channels() {
	std::cout << "Socketserver constructor called" << std::endl;
	Logger::set_server(*this);
	poller.addEvent(*this);
	poller.addEvent(sig);
}

Server::Server(const Server& copy)
: sock_fd(copy.sock_fd), m_conns(copy.m_conns), poller(copy.poller) {
}

Server::~Server(void) {
	std::cout << "Socketserver destructor called" << std::endl;
}

void Server::run(void) {
	poller.run();
}

void Server::stop(void) {
	poller.stop();
}

void	Server::notify(void) {
	int cfd;

	std::cout << "\nSending notification" << std::endl;
	cfd = accept(sock_fd, NULL, NULL);
	if (cfd == -1) {
		ERROR(handleSysError("accept"));
	} else {
		std::cout << "Connexion fd created: " << cfd << std::endl;
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


void	Server::response(const Connexion& conn, const std::string& msg) {
	/* temporary CRLF check during development */
	if (msg.size() < 2) { throw std::runtime_error("invalid message"); }
	if (msg[msg.size() - 2] != '\r' and msg[msg.size() - 1] != '\n')
		throw std::runtime_error("missing CRLF");
	/* ************************************** */
	Logger::send(msg);
	if (send(conn.getFd(), msg.c_str(), msg.size(), 0) == -1) {
		// ...
	}
}


Server& Server::operator=(const Server& copy) {
	if (this != &copy) {
	}
	return *this;
}

// -- accessors ---------------------------------------------------------------

std::size_t Server::get_nb_conns(void) const {
	return m_conns.size();
}

const std::string& Server::get_addr(void) const {
	return s_info.addr;
}

const std::string& Server::get_port(void) const {
	return s_info.port;
}

const std::string& Server::get_password(void) const {
	return s_info.password;
}

const std::string& Server::get_name(void) const {
	return s_info.name;
}

bool Server::has_password(void) const {
	return not s_info.password.empty();
}


