/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:59:22 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/01 02:37:51 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "io_event.hpp"
#include "connexion.hpp"
#include "epoll.hpp"
#include "signal.hpp"

#include <map>

struct ServerInfo {
	std::string name;
	std::string addr;
	std::string port;
	std::string password;
};


class Server : public IOEvent {

	public:
		Server(const ServerInfo&, const int, Signal&);
		~Server(void);
		Server(const Server&);
		Server& operator=(const Server&);

		void 				run(void);
		void 				stop(void);


		void				notify(void);
		int					getFd(void) const;
		void				disconnect(void);

		void 				unmapConnexion(const Connexion&);


		void response(const Connexion&, const std::string&);


		const std::string&	get_name(void) const;
		const std::string&	get_addr(void) const;
		const std::string&	get_port(void) const;
		const std::string&	get_password(void) const;
		std::size_t			get_nb_conns(void) const;
		bool 				has_password(void) const;

	private:

		ServerInfo					s_info;
		Shared_fd					sock_fd;
		std::map<int, Connexion>	m_conns;
		Poll						poller;
};

#endif
