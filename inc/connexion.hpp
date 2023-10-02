/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:41:28 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:52:26 by diroyer          ###   ########.fr       */
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
# include "send_info.hpp"

class Server;

struct ClientInfo {
	std::string username;
	std::string	hostname;
	std::string	servername;
	std::string	realname;
	std::string	nickname;
};

class Connexion : public IOEvent {
	public:
		Connexion(void);
		Connexion(int);
		~Connexion(void);
		Connexion(const Connexion&);
		Connexion& operator=(const Connexion&);

		void						read(void);
		void						write(void);
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
		void						mod_event(void);
};


#endif
