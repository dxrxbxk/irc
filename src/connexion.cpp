/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:41:30 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/01 23:32:57 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "connexion.hpp"

#define BUFFER_SIZE 1024

Connexion::Connexion(void)
: sock_fd(-1), buffer(), s_ptr(NULL), _registered(false) {
}

Connexion::~Connexion(void) {}

Connexion::Connexion(int fd, Server &server)
: sock_fd(fd), buffer(), s_ptr(&server), _registered(false) {
}

void	Connexion::set_register(void) {
	_registered = true;
}

bool	Connexion::registered(void) const {
	return _registered;
}

ClientInfo&	Connexion::get_client_info(void) {
	return s_client_info;
}

void	Connexion::setFd(int fd) {
	sock_fd = fd;
}

int		Connexion::getFd(void) const {
	return sock_fd;
}

Server&	Connexion::getServer(void) const {
	return *s_ptr;
}

std::string getResponse(void) {
	std::string response = ":localhost CAP * LS :";
	std::string cap = "cap1 cap2 cap3";
	std::string crlf = "\r\n";

	return response + cap + crlf;
}

void	Connexion::readInput(void) {
	ssize_t		rec_len;
	char		read_buf[BUFFER_SIZE];

	rec_len = recv(sock_fd, read_buf, BUFFER_SIZE, 0);
	if (rec_len == -1)
		ERROR(handleSysError("recv"));
	else {
		buffer.append(read_buf, rec_len);
	}
}

l_str	Connexion::checkCrlf(void) {
	std::string::size_type	pos;
	l_str					l_msg;
	while ((pos = buffer.find("\r\n")) != std::string::npos) {
		l_msg.push_back(buffer.substr(0, pos + 2));
		buffer.erase(0, pos + 2);
	}
	return l_msg;
}


void	Connexion::notify(void) {
	l_str		l_msg;

	readInput();
	l_msg = checkCrlf();

	for (l_str::const_iterator i = l_msg.begin(); i != l_msg.end(); ++i) {

		Logger::recv(*i);

		try {
			// parse raw message
			Message msg = Parser::parse(*i);
			msg.print();

			Command* cmd = CommandFactory::create(*this, msg);

			if (cmd == NULL)
				Logger::info(msg.get_command() + ": command not found");
			else {
				if (cmd->evaluate() == true)
					cmd->execute();
				delete cmd;
			}

		} catch (const std::exception& e) {
			Logger::info("Parsing error: " + std::string(e.what()));
		}
	}
}


void	Connexion::disconnect(void) {
	if (s_ptr) {
		Logger::info("connexion closed");
		s_ptr->unmapConnexion(*this);
	}
}

Connexion::Connexion(const Connexion &copy) {
	*this = copy;
}

Connexion& Connexion::operator=(const Connexion &copy) {
	if (this != &copy) {
		sock_fd = copy.sock_fd;
		buffer = copy.buffer;
		s_ptr = copy.s_ptr;
		s_client_info = copy.s_client_info;
		_registered = copy._registered;
	}
	return *this;
}
