/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:41:30 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 03:55:03 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "connexion.hpp"

#define BUFFER_SIZE 1024

Connexion::Connexion(void)
:	_socket(),
	_info(),
	_buffer_in(),
	_buffer_out(),
	_registered(false),
	_wait_out(false) {
}

Connexion::~Connexion(void) {}

Connexion::Connexion(int fd)
:	_socket(fd),
	_info(),
	_buffer_in(),
	_buffer_out(),
	_registered(false),
	_wait_out(false) {
}


Connexion::Connexion(const Connexion& other)
:	_socket(other._socket),
	_info(other._info),
	_buffer_in(other._buffer_in),
	_buffer_out(other._buffer_out),
	_registered(other._registered),
	_wait_out(other._wait_out) {
}

Connexion& Connexion::operator=(const Connexion &other) {
	if (this != &other) {
		      _info = other._info;
		    _socket = other._socket;
		 _buffer_in = other._buffer_in;
		_buffer_out = other._buffer_out;
		_registered = other._registered;
		  _wait_out = other._wait_out;
	}
	return *this;
}





// -- connexion accessors ------------------------------------------------------

void	Connexion::set_register(void) {
	_registered = true;
}

bool	Connexion::registered(void) const {
	return _registered;
}






void	Connexion::readInput(void) {
	ssize_t		rec_len;
	char		read_buf[BUFFER_SIZE];

	rec_len = recv(_socket, read_buf, BUFFER_SIZE, 0);
	if (rec_len == -1)
		ERROR(handleSysError("recv"));
	else {
		_buffer_in.append(read_buf, rec_len);
	}
}

l_str	Connexion::checkCrlf(void) {
	std::string::size_type	pos;
	l_str					l_msg;
	while ((pos = _buffer_in.find("\r\n")) != std::string::npos) {
		l_msg.push_back(_buffer_in.substr(0, pos + 2));
		_buffer_in.erase(0, pos + 2);
	}
	return l_msg;
}

void	Connexion::mod_event(int flag) {
	Server::shared().get_poller().modEvent(*this, flag);
}




// -- IOEvent methods ----------------------------------------------------------


int		Connexion::fd(void) const {
	return _socket;
}


void	Connexion::write(void) {

	/* temporary CRLF check during development */
	// if (_buffer_out.size() < 2)
	// 	throw std::runtime_error("invalid message");
	// if (_buffer_out[_buffer_out.size() - 2] != '\r'
	// and _buffer_out[_buffer_out.size() - 1] != '\n')
	// 	throw std::runtime_error("missing CRLF");
	/* ************************************** */


	Logger::send(_buffer_out);
	if (::send(_socket, _buffer_out.c_str(), _buffer_out.size(), 0) == -1) {
		// clear buffer if error is EAGAIN
		// EAGAIN means that the socket is not ready for writing
	}

	_buffer_out.clear();

	// this->mod_event(EPOLLIN);
	// _wait_out = false;
}




void	Connexion::read(void) {

	readInput();

	const l_str l_msg = checkCrlf();

	for (l_str::const_iterator i = l_msg.begin(); i != l_msg.end(); ++i) {

		Logger::recv(*i);

		try {
			// parse raw message
			Message msg = Parser::parse(*i);
			msg.print();

			Command* cmd = CommandFactory::create(*this, msg);

			if (cmd == NULL)
				Logger::info(msg.command() + " <- COMMAND NOT FOUND :(");
			else {
				cmd->execute();
				if (not _buffer_out.empty())
					write();
				delete cmd;
			}
		} catch (const std::exception& e) {
			Logger::info("Parsing error: " + std::string(e.what()));
		}

	}
}

void	Connexion::disconnect(void) {
	Logger::info("connexion closed");
	Server::shared().unmap_connexion(*this);
}


void	Connexion::enqueue(const std::string &msg) {
	_buffer_out.append(msg);
	write();
	return;
	if (not _wait_out) {
		this->mod_event(EPOLLOUT | EPOLLIN);
		_wait_out = true;
	}
}





// -- info accessors -----------------------------------------------------------

ClientInfo&	Connexion::info(void) {
	return _info;
}

const ClientInfo&	Connexion::info(void) const {
	return _info;
}

void Connexion::info(const ClientInfo& info) {
	_info = info;
}

void Connexion::info(ClientInfo& info) {
	_info.username.swap(info.username);
	_info.hostname.swap(info.hostname);
	_info.realname.swap(info.realname);
	_info.nickname.swap(info.nickname);
}






std::string&	Connexion::nickname(void) {
	return _info.nickname;
}

const std::string&	Connexion::nickname(void) const {
	return _info.nickname;
}

void Connexion::nickname(const std::string& nickname) {
	_info.nickname = nickname;
}

void Connexion::nickname(std::string& nickname) {
	_info.nickname.swap(nickname);
}



std::string&	Connexion::username(void) {
	return _info.username;
}

const std::string&	Connexion::username(void) const {
	return _info.username;
}

void Connexion::username(const std::string& username) {
	_info.username = username;
}

void Connexion::username(std::string& username) {
	_info.username.swap(username);
}



std::string&	Connexion::hostname(void) {
	return _info.hostname;
}

const std::string&	Connexion::hostname(void) const {
	return _info.hostname;
}

void Connexion::hostname(const std::string& hostname) {
	_info.hostname = hostname;
}

void Connexion::hostname(std::string& hostname) {
	_info.hostname.swap(hostname);
}


std::string&	Connexion::realname(void) {
	return _info.realname;
}

const std::string&	Connexion::realname(void) const {
	return _info.realname;
}

void Connexion::realname(const std::string& realname) {
	_info.realname = realname;
}

void Connexion::realname(std::string& realname) {
	_info.realname.swap(realname);
}
