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

void Server::init(ServerInfo& info, const Shared_fd& socket) {

	_info = info;
	_socket = socket;

	Logger::set_server(*this);
	_poller.add_event(*this);

	_poller.add_event(Logger::shared());
	// _poller.addEvent(Signal::shared());

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

	_conns[cfd] = Connexion(cfd);
	_poller.add_event(_conns[cfd]);
}

int Server::fd(void) const {
	return _socket;
}

void Server::disconnect(void) {
	Logger::info("server disconnected");
}




// -- channel methods ---------------------------------------------------------


Channel&	Server::get_channel(const std::string& channel_name, Connexion &ref) {
	std::size_t size = _channels.count(channel_name);
	Logger::debug(utils::to_string(size));
	if (not _channels.count(channel_name)) {
		Logger::debug("create channel!");
		_channels[channel_name] = Channel(channel_name, ref);
	}
	return _channels[channel_name];
}

bool	Server::channel_exist(const std::string& channel) const {
	return _channels.count(channel);
}

Channel& Server::create_channel(const std::string& name, Connexion& creator) {
	// Channel& channel = _channels[name] = Channel(name, creator);
	return _channels[name] = Channel(name, creator);
}

Channel& Server::channel(const std::string& name) {
	return _channels[name];
}



/* remove connexion */
void Server::unmap_connexion(const Connexion& conn) {
	_conns.erase(conn.fd());
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


