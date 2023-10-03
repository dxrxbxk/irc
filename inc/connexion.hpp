/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:41:28 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 04:04:01 by diroyer          ###   ########.fr       */
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
		int							fd(void) const;
		void						disconnect(void);
		void						enqueue(const std::string&);

		void						set_register(void);
		bool						registered(void) const;


		// -- public info accessors -------------------------------------------

		/* client info */
		ClientInfo&					info(void);
		const ClientInfo&			info(void) const;
		void						info(const ClientInfo&);
		void						info(ClientInfo&);

		/* nickname */
		std::string&				nickname(void);
		const std::string&			nickname(void) const;
		void						nickname(const std::string&);
		void						nickname(std::string&);

		/* username */
		std::string&				username(void);
		const std::string&			username(void) const;
		void						username(const std::string&);
		void						username(std::string&);

		/* hostname */
		std::string&				hostname(void);
		const std::string&			hostname(void) const;
		void						hostname(const std::string&);
		void						hostname(std::string&);

		/* realname */
		std::string&				realname(void);
		const std::string&			realname(void) const;
		void						realname(const std::string&);
		void						realname(std::string&);


	private:

		// -- private members -------------------------------------------------

		Shared_fd					_socket;
		ClientInfo					_info;
		std::string					_buffer_in;
		std::string					_buffer_out;
		bool						_registered;
		bool						_wait_out;

		void						readInput(void);
		l_str						checkCrlf(void);
		void						mod_event(int flag);
};


#endif
