/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socketserver.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:59:22 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/21 23:30:58 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKETSERVER_HPP
# define SOCKETSERVER_HPP

#include "io_event.hpp"
#include "connexion.hpp"
#include "epoll.hpp"
#include "signal.hpp"

#include <map>

struct ServerInfo {
	const std::string node;
	const std::string service;
	const std::string password;
};


class Server : public IOEvent {

	public:
		Server(const ServerInfo&, const int, Signal&);
		~Server(void);
		Server(const Server&);
		Server& operator=(const Server&);

		void		notify(void);
		int			getFd(void) const;
		void		disconnect(void);

		void unmapConnexion(const Connexion&);


		void send(const Connexion&, const std::string&);


		const std::string& get_node(void) const;
		const std::string& get_service(void) const;
		const std::string& get_password(void) const;
		bool has_password(void) const;

	private:

		ServerInfo					s_info;
		Shared_fd					sock_fd;
		std::map<int, Connexion>	m_conns;
		Poll						poller;
};

#endif






