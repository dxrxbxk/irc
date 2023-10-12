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
#include "channel.hpp"
#include "utils.hpp"
#include <stdexcept>

Connexion::Connexion(void)
:	_socket(),
	_info(),
	_buffer_in(),
	_buffer_out(),
	_registered(false),
	_wait_out(false),
	_channels(),
	_tracker(0) {
}

Connexion::~Connexion(void) {
	leave_channels();

}

Connexion::Connexion(int fd)
:	_socket(fd),
	_info(),
	_buffer_in(),
	_buffer_out(),
	_registered(false),
	_wait_out(false),
	_channels(),
	_tracker(0) {
}

Connexion::Connexion(const Connexion& other)
:	_socket(other._socket),
	_info(other._info),
	_buffer_in(other._buffer_in),
	_buffer_out(other._buffer_out),
	_registered(other._registered),
	_wait_out(other._wait_out),
	_channels(other._channels),
	_tracker(other._tracker) {
}

Connexion& Connexion::operator=(const Connexion &other) {
	if (this != &other) {
		      _info = other._info;
		    _socket = other._socket;
		 _buffer_in = other._buffer_in;
		_buffer_out = other._buffer_out;
		_registered = other._registered;
		  _wait_out = other._wait_out;
		  _channels = other._channels;
		  _tracker  = other._tracker;
	}
	return *this;
}

// -- connexion accessors ------------------------------------------------------

const std::string Connexion::fullname(void) {
		return (nickname() + "!" + username() + "@" + hostname());
}

void Connexion::login(void) {
	_registered = true;
	ClientInfo&	info = this->info();
	enqueue(RPL::welcome(info));
	enqueue(RPL::motd_start(info));
	enqueue(RPL::motd(info, Server::shared().motd()));
	enqueue(RPL::end_of_motd(info));
}

bool	Connexion::can_register(void) {
	return (_tracker & NICK && _tracker & USER && _tracker & PASS);
}

void Connexion::logout(void) {
	_registered = false;
}

bool Connexion::registered(void) const {
	return _registered;
}

// -- public channel methods ---------------------------------------------------

void Connexion::enter_channel(Channel& channel) {
	if (static_cast<int>(channel.size()) >= channel.limit())
		throw std::runtime_error("channel is full");
	channel.add_user(*this);
	_channels.insert(&channel);
}

void Connexion::leave_channel(Channel& channel) {
//	channel.remove_user(*this);
	_channels.erase(&channel);
	//Logger::info("channel size: " + utils::to_string(channel.size()));
//	if (channel.size() == 0) {
//		Server::shared().remove_channel(channel.name());
//	}
}

void Connexion::leave_channels(void) {
	std::set<Channel*>::iterator tmp;

	for (std::set<Channel*>::iterator it = _channels.begin();
			it != _channels.end();) {
		tmp = it;
		++it;
		(*tmp)->remove_user(*this);
	}
}

void	Connexion::tracker(int flag) {
	_tracker |= flag;
}

int		Connexion::tracker(void) {
	return _tracker;
}

void	Connexion::read_input(void) {
	ssize_t		readed;
	char		buffer[BUFFER_SIZE];

	readed = ::recv(_socket, buffer, BUFFER_SIZE, 0);
	if (readed == -1)
		throw::std::runtime_error(handleSysError("recv"));
	else {
		_buffer_in.append(buffer, readed);
	}
}

l_str	Connexion::check_crlf(void) {
	std::string::size_type	pos;
	l_str					l_msg;
	while ((pos = _buffer_in.find("\r\n")) != std::string::npos) {
		l_msg.push_back(_buffer_in.substr(0, pos + 2));
		_buffer_in.erase(0, pos + 2);
	}
	return l_msg;
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
	Server::shared().poller().mod_event(*this, EPOLLIN);
	_wait_out = false;
}


void Connexion::read(void) {

	read_input();

	const l_str l_msg = check_crlf();

	for (l_str::const_iterator i = l_msg.begin(); i != l_msg.end(); ++i) {

		Logger::recv(*i);

		try {
			// parse raw message
			Message msg = Parser::parse(*i);
			msg.print();

			Command* cmd = CommandFactory::create(*this, msg);

			if (cmd == NULL) {
				Logger::info(msg.command() + " command not found");
			}
			else {
				int ret = cmd->execute();
				delete cmd;
				if (ret == -1) {
				//	disconnect();
//					return ;
				}
			}
		} catch (const std::exception& e) {
			Logger::info("Error" + std::string(e.what()));
		}
	}
}

void Connexion::disconnect(void) {
	Logger::info("connexion closed");
	Server::shared().add_rm_list(*this);
}

void Connexion::enqueue(const std::string &msg) {
	_buffer_out.append(msg);
	if (not _wait_out) {
		Server::shared().poller().mod_event(*this, EPOLLOUT);
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
