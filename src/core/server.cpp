/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:59:12 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:53:47 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#include "utils.hpp"
#define BUFFER_SIZE 1024

Server::Server(void)
:	_initialized(false),
	_info(),
	_socket(),
	_poller(),
	_channels(),
	_conns(),
	_nicks(),
	_rm_list(),
	_motd(message_irc)
{
}

Server::Server(const Server&) {}

Server::~Server(void) {}

Server& Server::operator=(const Server&) { return *this; }

// -- public static methods ----------------------------------------------------

Server& Server::shared(void) {
	static Server instance;
	return instance;
}

void Server::init(ServerInfo& info, const Shared_fd& socket) {
	if (_initialized == true)
		throw std::runtime_error("server already initialized");

	_info = info;
	_socket = socket;

	Logger::set_server(*this);
	_poller.add_event(*this, _socket);

	_poller.add_event(Logger::shared());
	_poller.add_event(Signal::shared());

	_initialized = true;

}

// print channel and users in it with _channels and _nicks
void Server::print_channels(void) const {
	channel_iterator it = _channels.begin();
	while (it != _channels.end()) {
		std::cout << "channel: " << it->first << std::endl;
		it->second.print_users();
		++it;
	}
}




void Server::run(void) {
	Logger::start();
	while (_initialized == true)
	{
		// refresh logger print
		Logger::render();
		_poller.run();
		Logger::info(utils::to_string(_channels.size()) + " channels");
		print_channels();
		remove_rm_list();
		rm_channels();
	}
	Logger::end();
}

void Server::stop(void) {
	_initialized = false;
}

void	Server::accept(void) {
	int cfd;

	Logger::info("new socket connexion");

	cfd = ::accept(_socket, NULL, NULL);

	if (cfd == -1) {
		ERROR(handleSysError("accept"));
		return; }

	Logger::info("connexion accepted");

	Connexion& conn = _conns[cfd] = Connexion(cfd);
	_poller.add_event(conn);
}


l_str	Server::check_crlf(void) {
	std::string::size_type	pos;
	l_str					l_msg;
	while ((pos = _buffer_in.find("\r\n")) != std::string::npos) {
		l_msg.push_back(_buffer_in.substr(0, pos + 2));
		_buffer_in.erase(0, pos + 2);
	}
	return l_msg;
}

void	Server::read_input(void) {
	ssize_t		readed;
	char		buffer[BUFFER_SIZE];

	readed = ::recv(_socket, buffer, BUFFER_SIZE, 0);
	if (readed == -1)
		throw::std::runtime_error(handleSysError("recv"));
	else {
		_buffer_in.append(buffer, readed);
	}
}

void Server::read(void) {
	accept();
}

void	Server::write(void) {
}

int Server::fd(void) const {
	return _socket;
}

void Server::disconnect(void) {
	Logger::info("server disconnected");
}

// -- channel methods ---------------------------------------------------------
/*
bool Server::in_channel(std::string& channel_name, std::string& user) {
	return _channels[channel_name].in_channel(user);
}
*/
void	Server::broadcast(const std::string& msg) {
	Logger::debug("server BROADCAST to users");
	for (nick_iterator it = _nicks.begin(); it != _nicks.end(); ++it) {
			it->second->enqueue(msg);
	}
}

void	Server::broadcast(const std::string& msg, const Connexion& sender) {
	Logger::debug("server BROADCAST to users");
	for (nick_iterator it = _nicks.begin(); it != _nicks.end(); ++it) {
		if (it->second != &sender)
			it->second->enqueue(msg);
	}
}

Channel&	Server::channel(const std::string& channel_name) {
	return _channels[channel_name];
}

Channel&	Server::get_channel(const std::string& channel_name) {
	return _channels[channel_name];
}


Channel& Server::create_channel(const std::string& name, Connexion& creator) {
	// Channel& channel = _channels[name] = Channel(name, creator);

	creator.enqueue(":" + creator.nickname() + " NICK " + "@" + creator.nickname() + CRLF);
//	_server.ch_nick(_conn, first);
	return _channels[name] = Channel(name, creator);
}

bool	Server::channel_exist(const std::string& name) const {
	return _channels.count(name);
}

void	Server::remove_channel(const std::string& name) {
	_channels.erase(name);
}

void	Server::ch_nick(Connexion& conn, std::string& new_nick) {	
	_nicks[new_nick] = &conn;
	_nicks.erase(conn.nickname());
	conn.nickname(new_nick);
}

bool	Server::nick_exist(const std::string& nick) {
	return _nicks.count(nick);
}

Connexion& Server::get_conn(const std::string& nick) {
	return *_nicks[nick];
}

void Server::accept_newcomer(Connexion& conn) {
	_nicks[conn.nickname()] = &conn;
}

std::string& Server::motd(void) {
	return _motd;
}

// -- public accessors --------------------------------------------------------

std::size_t Server::get_nb_conns(void) const {
	return _conns.size();
}

const std::string& Server::address(void) const {
	return _info.addr;
}

const std::string& Server::port(void) const {
	return _info.port;
}

const std::string& Server::password(void) const {
	return _info.password;
}

const std::string& Server::name(void) const {
	return _info.name;
}

bool Server::has_password(void) const {
	return not _info.password.empty();
}

Poll&	Server::poller(void) {
	return _poller;
}

void Server::add_rm_channel(Channel& channel) {
	_rm_channels.push(&channel);
}

void Server::rm_channels(void) {
	while (!_rm_channels.empty())
	{
		Channel& channel = *_rm_channels.top();
		_channels.erase(channel.name());
		_rm_channels.pop();
	}
}

void Server::add_rm_list(Connexion& conn) {
	_rm_list.push(&conn);
}

void Server::remove_rm_list(void) {
	while (!_rm_list.empty())
	{
		Connexion& conn = *_rm_list.top();
		_poller.del_event(conn);
		_nicks.erase(conn.nickname());
		_conns.erase(conn.fd());
		_rm_list.pop();
	}
}




