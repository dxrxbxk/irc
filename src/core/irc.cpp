/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 03:30:50 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 22:32:20 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"
#define BUFFER 1024
#define BACKLOG 5


Irc::Irc(void) {}

Irc::~Irc(void) {}

int Irc::start(const std::string& port, const std::string& password) {

	try {
		ServerInfo info = {"straboul", "127.0.0.1", port, ""};

		Shared_fd sock = create("127.0.0.1", port);

		Signal::signal_ignore();
		Signal::signal_manager();

		Server& server = Server::shared();

		server.init(info, sock);
		server.run();
		return EXIT_SUCCESS;

	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
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



int Irc::create_socket(const std::string& port) {

	const struct sockaddr_in addr = {
		AF_INET, htons(utils::to_integer<unsigned short>
		(port, "invalid port")), INADDR_ANY, {0},
	};

	const int socket = ::socket(AF_INET, SOCK_STREAM, 0);

	if (socket == -1)
		throw std::runtime_error(handleSysError("socket"));


	if (::bind(socket, (struct sockaddr *)&addr, sizeof(addr)) == -1)
		throw std::runtime_error(handleSysError("bind"));

	if (::listen(socket, SOMAXCONN) == -1)
		throw std::runtime_error(handleSysError("listen"));

	return socket;
}



void Irc::getSocketInfo(const int fd) {
	struct sockaddr_in peer;
	socklen_t addrlen;

	addrlen = sizeof(peer);
	memset(&peer, 0, sizeof(struct sockaddr));
	if (getsockname(fd, (struct sockaddr *)&peer, &addrlen) == -1)
		throw std::runtime_error(handleSysError("getsockname"));
	std::cout << "IP address: " << custom_inet_ntoa(peer.sin_addr) << std::endl;
	std::cout << "Port: " << ntohs(peer.sin_port) << std::endl;
}

int		Irc::create(const std::string& node, const std::string& service) {

	struct addrinfo 		hints;
	struct addrinfo 		*result, *rp;
	int 					ret_gai = -1;
	int						sfd = -1;
	int 					sock_opt = 1;

	std::cout << "Creating an endpoint for communication" << std::endl;

	init(&hints);
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
		getSocketInfo(sfd);
	if (listen(sfd, BACKLOG) == -1)
		throw std::runtime_error(handleSysError("listen"));

	return sfd;
}
