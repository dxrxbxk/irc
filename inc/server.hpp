/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:59:22 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 02:12:22 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "io_event.hpp"
# include "connexion.hpp"
# include "channel.hpp"
# include "epoll.hpp"
# include "signal.hpp"
# include "sharedfd.hpp"

# include <map>


struct ServerInfo {
	std::string name;
	std::string addr;
	std::string port;
	std::string password;
};


class Server : public IOEvent {


	public:

		/* initialize server */
		void init(ServerInfo&, const Shared_fd&, Signal&);

		/* run server */
		void run(void);

		/* stop server */
		void stop(void);


		// -- IOEvent methods ---------------------------------------------------

		void notify(void);
		int getFd(void) const;
		void disconnect(void);


		// -- public methods ----------------------------------------------------

		void response(const Connexion&, const std::string&);

		void unmap_connexion(const Connexion&);



		// -- public accessors -------------------------------------------------

		const std::string&	get_name(void) const;
		const std::string&	get_addr(void) const;
		const std::string&	get_port(void) const;
		const std::string&	get_password(void) const;
		std::size_t			get_nb_conns(void) const;
		bool 				has_password(void) const;


		// -- public static methods --------------------------------------------

		static Server& shared(void);


	private:


		// -- private constructors ---------------------------------------------

		Server(void);
		~Server(void);
		Server(const Server&);
		Server& operator=(const Server&);


		// -- private types ----------------------------------------------------

		typedef std::map<int, Connexion>		conn_map;
		typedef std::map<std::string, Channel>	channel_map;


		// -- private members --------------------------------------------------

		bool			_initialized;
		ServerInfo		_info;
		Shared_fd		_socket;
		Poll			_poller;
		conn_map		_conns;
		channel_map 	_channels;
};

#endif
