/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connexion.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 15:41:28 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 22:31:45 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNEXION_HPP
# define CONNEXION_HPP

# include <iostream>
# include <string>
# include <sys/socket.h>
# include <sstream>
# include <map>
# include <set>

# include "io_event.hpp"
# include "utils.hpp"
# include "sharedfd.hpp"
# include "parser.hpp"
# include "types.hpp"
# include "command_factory.hpp"
# include "numerics.hpp"

class Server;
class Channel;

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

		void						login(void);
		void						logout(void);
		bool						registered(void) const;

		// -- public channel methods ------------------------------------------

		void						enter_channel(Channel&);
		void						leave_channel(Channel&);
		void						leave_channels(void);




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
		std::set<Channel*>			_channels;


		// -- private enums ---------------------------------------------------

		enum { BUFFER_SIZE = 1024 };


		// -- private methods -------------------------------------------------

		void						read_input(void);
		l_str						check_crlf(void);
};


#endif
