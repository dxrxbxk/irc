/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 03:32:53 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/24 07:22:44 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstdio>
# include <string>
# include <cstring>
# include <cstdlib>
# include <cerrno>
# include <sstream>
# include <csignal>
# include <map>
# include <vector>

# include <arpa/inet.h>
# include <poll.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netinet/tcp.h>
# include <unistd.h>
# include <sys/types.h>
# include <netdb.h>
# include <sys/wait.h>

# include "utils.hpp"
# include "signal.hpp"
# include "sharedfd.hpp"
# include "server.hpp"

// sfd = server fd
// cfd = connexion fd (accept())

class Irc {
	public:
		Irc(void);
		~Irc(void);

		void						run(void);

	private:

		void						init(struct addrinfo *hints);
		int							create(std::string, std::string);
		void						getSocketInfo(int fd); // could be public

		Signal						pipe;
		std::vector<Server>			v_sock;
};

#endif
