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

Server::Server(void)
:	_initialized(false),
	_info(),
	_socket(),
	_poller(),
	_conns(),
	_channels() {
}


Server::Server(const Server&) {}

Server::~Server(void) {}

Server& Server::operator=(const Server&) { return *this; }


// -- public static methods ----------------------------------------------------

Server& Server::shared(void) {
	static Server instance;
	return instance;
}

void Server::init(ServerInfo& info, const Shared_fd& socket, Signal& signal) {

	_info = info;
	_socket = socket;

	Logger::set_server(*this);
	_poller.addEvent(*this);
	_poller.addEvent(signal);

	_initialized = true;

}

void Server::run(void) {
	if (_initialized == true)
		_poller.run();
}

void Server::stop(void) {
	_poller.stop();
}



void	Server::write(void) {}

void	Server::read(void) {
	int cfd;

	Logger::info("new socket connexion");

	cfd = ::accept(_socket, NULL, NULL);

	if (cfd == -1) {
		ERROR(handleSysError("accept"));
		return; }

	Logger::info("connexion accepted");

	(_conns)[cfd] = Connexion(cfd);
	_poller.addEvent((_conns)[cfd]);
}

int Server::fd(void) const {
	return _socket;
}

void Server::disconnect(void) {
	Logger::info("server disconnected");
}




// -- channel methods ---------------------------------------------------------


Channel&	Server::get_channel(const std::string& channel_name, Connexion &ref) {
	if (not _channels.count(channel_name))
		_channels[channel_name] = Channel(channel_name, ref);
	return _channels[channel_name];
}

bool	Server::channel_exist(const std::string& channel) const {
	return _channels.count(channel);
}



/* remove connexion */
void Server::unmap_connexion(const Connexion& conn) {
	_conns.erase(conn.fd());
}



// -- public accessors --------------------------------------------------------

std::size_t Server::get_nb_conns(void) const {
	return _conns.size();
}

const std::string& Server::get_addr(void) const {
	return _info.addr;
}

const std::string& Server::get_port(void) const {
	return _info.port;
}

const std::string& Server::get_password(void) const {
	return _info.password;
}

const std::string& Server::get_name(void) const {
	return _info.name;
}

bool Server::has_password(void) const {
	return not _info.password.empty();
}

Poll&	Server::get_poller(void) {
	return _poller;
}


