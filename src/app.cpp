/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 03:30:50 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/01 00:28:12 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "app.hpp"
#define BUFFER 1024
#define BACKLOG 5


Irc::Irc()
: pipe() {
	std::cout << "Server constructor called" << std::endl;
}

Irc::~Irc() {
	std::cout << "Server destructor called" << std::endl;
}

void Irc::run(void) {
	try {
		signalIgnore();

		ServerInfo info = {"straboul", "127.0.0.1", "8080", ""};

		Shared_fd sock = this->create(info.addr, info.port);

		signalManager();

		Server& server = Server::shared();

		server.init(info, sock, pipe);
		server.run();

	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

void Irc::init(struct addrinfo *hints) {
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = AI_PASSIVE;
	hints->ai_protocol = 0; /* Any protocol */
	hints->ai_canonname = NULL;
	hints->ai_addr = NULL;
	hints->ai_next = NULL;
}

void Irc::getSocketInfo(int fd) {
	struct sockaddr_in peer;
	socklen_t addrlen;

	addrlen = sizeof(peer);
	memset(&peer, 0, sizeof(struct sockaddr));
	if (getsockname(fd, (struct sockaddr *)&peer, &addrlen) == -1)
		throw std::runtime_error(handleSysError("getsockname"));
	std::cout << "IP address: " << custom_inet_ntoa(peer.sin_addr) << std::endl;
	std::cout << "Port: " << ntohs(peer.sin_port) << std::endl;
}

int		Irc::create(std::string node, std::string service) {

	struct addrinfo 		hints;
	struct addrinfo 		*result, *rp;
	int 					ret_gai = -1;
	int						sfd = -1;
	int 					sock_opt = 1;

	std::cout << "Creating an endpoint for communication" << std::endl;

	this->init(&hints);
	ret_gai = getaddrinfo(node.c_str(), service.c_str(), &hints, &result);
	if (ret_gai != 0) {
		throw std::runtime_error(handleGaiError(ret_gai));
	}

	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1)
			continue;

		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &sock_opt,
					sizeof(int)) == -1)
			throw std::runtime_error(handleSysError("setsockopt"));

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;

		close(sfd);
		sfd = -1;
	}

	freeaddrinfo(result);

	if (rp == NULL)
		throw std::runtime_error(handleSysError("bind"));
	else
		this->getSocketInfo(sfd);
	if (listen(sfd, BACKLOG) == -1)
		throw std::runtime_error(handleSysError("listen"));

	return sfd;
}
