/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 03:30:50 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/25 12:12:17 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"
#define BUFFER 1024
#define BACKLOG 5


Server::Server() : pipe(), poller(), v_sock() {
	std::cout << "Server constructor called" << std::endl;
}

Server::~Server() {
	std::cout << "Server destructor called" << std::endl;
}

void Server::run(void) {
	try {
		signalIgnore();
		std::string node = "0.0.0.0";
		std::string service = "8080";	


		v_sock.push_back(Socketserver(m_conns, poller, this->create(node, service)));
//		v_sock.push_back(Socketserver(m_conns, poller, this->create(NULL, "8090")));

		signalManager();

		std::cout << "Starting epoll()" << std::endl;

		std::cout << "fd write end " << g_signalPipe[0] << std::endl;
		std::cout << "fd read end " << g_signalPipe[1] << std::endl;
		
		poller.addEvent(pipe);

		std::cout << "Sfd vector size =" << v_sock.size() << std::endl;

		for (std::vector<Socketserver>::size_type i = 0; i < v_sock.size(); ++i) {
			poller.addEvent(v_sock[i]);
		}

		poller.run();

	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	}
}

void Server::init(struct addrinfo *hints) {
	memset(hints, 0, sizeof(struct addrinfo));
	hints->ai_family = AF_INET;
	hints->ai_socktype = SOCK_STREAM;
	hints->ai_flags = AI_PASSIVE;
	hints->ai_protocol = 0; /* Any protocol */
	hints->ai_canonname = NULL;
	hints->ai_addr = NULL;
	hints->ai_next = NULL;
}

void Server::getSocketInfo(int fd) {
	struct sockaddr_in peer;
	socklen_t addrlen;

	addrlen = sizeof(peer);
	memset(&peer, 0, sizeof(struct sockaddr));
	if (getsockname(fd, (struct sockaddr *)&peer, &addrlen) == -1)
		throw std::runtime_error(handleSysError("getsockname"));
	std::cout << "IP address: " << custom_inet_ntoa(peer.sin_addr) << std::endl;
	std::cout << "Port: " << ntohs(peer.sin_port) << std::endl;
}

int		Server::create(std::string node, std::string service) {

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
