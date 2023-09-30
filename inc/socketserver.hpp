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

#include "notification.hpp"
#include "connexion.hpp"
#include "epoll.hpp"

#include <map>

class Socketserver : public notification {

	public:
		Socketserver(std::map<int, Connexion>&, Poll&, int);
		~Socketserver();
		Socketserver(const Socketserver& copy);
		Socketserver&operator=(const Socketserver& copy);

		void		notify(void);
		int			getFd(void);
		void		disconnect(void);

	private:

		Shared_fd					sock_fd;
		std::map<int, Connexion>*	m_conns;
		Poll*						poller;
};

#endif






