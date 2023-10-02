/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:41:28 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 22:54:54 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNEXION_HPP
# define CONNEXION_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <sstream>
# include <map>

# include "io_event.hpp"
# include "utils.hpp"
# include "sharedfd.hpp"
# include "parser.hpp"
# include "types.hpp"
# include "command_factory.hpp"
# include "numerics.hpp"

class Server;

struct ClientInfo {
	std::string username;
	std::string	hostname;
	std::string	servername;
	std::string	realname;
	std::string	nickname;
};

struct SendInfo {
	int					reply;
	const std::string	send_buffer;
};

class Connexion : public IOEvent {
	public:
		Connexion(void);
		Connexion(int);
		~Connexion(void);
		Connexion(const Connexion&);
		Connexion& operator=(const Connexion&);

		void						read(void);
		int							getFd(void) const;
		void						setFd(int fd);
		void						disconnect(void);
		
		void						set_register(void);
		bool						registered(void) const;
		
		ClientInfo&					get_client_info(void);
		std::string					get_nickname(void);

	private:
		Shared_fd					sock_fd;
		std::string					buffer;
		ClientInfo					s_client_info;
		SendInfo					s_send_info;

		void						readInput(void);
		l_str						checkCrlf(void);
		bool						_registered;
};


#endif
