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
	_rm_list()
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

//	Logger::set_server(*this);
	_poller.add_event(*this);

	_poller.add_event(Logger::shared());
	_poller.add_event(Signal::shared());

	_initialized = true;

}

void Server::run(void) {
	Logger::start();
	while (_initialized == true)
	{
		// refresh logger print
		Logger::render();
		_poller.run();
		remove_rm_list();
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

void	Server::write(void) {
}

void	Server::read(void) {
	Server::accept();
}

int Server::fd(void) const {
	return _socket;
}

void Server::disconnect(void) {
	Logger::info("server disconnected");
}

// -- channel methods ---------------------------------------------------------

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

Channel&	Server::get_channel(const std::string& channel_name, Connexion &ref) {
	std::size_t size = _channels.count(channel_name);
	if (not _channels.count(channel_name)) {
		_channels[channel_name] = Channel(channel_name, ref);
	}
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

Channel& Server::channel(const std::string& name) {
	return _channels[name];
}


void	Server::ch_nick(Connexion& conn, std::string& new_nick) {	
	_nicks[new_nick] = &conn;
	_nicks.erase(conn.nickname());
	conn.nickname(new_nick);
}

bool	Server::nick_exist(const std::string& nick) {
	return _nicks.count(nick);
}


void Server::accept_newcomer(Connexion& conn) {
	_nicks[conn.nickname()] = &conn;
}

/*
void Server::remove_newcomer(const Connexion& conn) {
	_poller.del_event(conn);
	_news.erase(conn.fd());
}
*/

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




