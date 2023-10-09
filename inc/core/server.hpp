/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 22:59:22 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:48:52 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "types.hpp"
# include "io_event.hpp"
# include "connexion.hpp"
# include "channel.hpp"
# include "epoll.hpp"
# include "signal.hpp"
# include "sharedfd.hpp"
# include <stack>
#include <string>

struct ServerInfo {
	std::string name;
	std::string addr;
	std::string port;
	std::string password;

	ServerInfo() : name(), addr(), port(), password() {};

	~ServerInfo() {};

	ServerInfo(const std::string& n, const std::string& ip, const std::string& p, const std::string& cp)
        : name(n), addr(ip), port(p), password(cp) {}

	void add_password(std::string &p)		{ password.swap(p); } 
	void add_password(const std::string &p) { password = p; }

};

class Server : public IOEvent {

	public:

		/* initialize server */
		void init(ServerInfo&, const Shared_fd&);

		/* run server */
		void run(void);

		/* stop server */
		void stop(void);


		// -- IOEvent methods ---------------------------------------------------

		void				read(void);
		void				write(void);
		int					fd(void) const;
		void				disconnect(void);


		// -- public methods ----------------------------------------------------

		void	ch_nick(Connexion&, std::string&);
		bool	nick_exist(const std::string&);

		void	accept_newcomer(Connexion&);
		void	remove_newcomer(const Connexion&);

		void	broadcast(const std::string&, const Connexion&);
		void	broadcast(const std::string& msg);

		void	accept(void);

		// -- public accessors -------------------------------------------------

		const std::string&	name(void) const;
		const std::string&	port(void) const;
		const std::string&	address(void) const;
		const std::string&	password(void) const;
		std::size_t			get_nb_conns(void) const;
		Poll&				poller(void) ;

		bool 				has_password(void) const;

		Channel&	get_channel(const std::string&, Connexion &ref);
		Channel&	channel(const std::string&);
		bool		channel_exist(const std::string&) const;
		Channel&	create_channel(const std::string&, Connexion&);

		void	 add_rm_list(Connexion&);
		void	 remove_rm_list(void);

		void			motd(const std::string&);
		std::string&	motd(void);

		// -- public static methods --------------------------------------------

		static Server& shared(void);


	private:

		typedef std::map<std::string, Channel>::const_iterator		channel_iterator;
		typedef std::map<std::string, Connexion*>::const_iterator	nick_iterator;

		// -- private constructors ---------------------------------------------

		Server(void);
		~Server(void);
		Server(const Server&);
		Server& operator=(const Server&);

		// -- private types ----------------------------------------------------

		typedef std::map<int, Connexion>			conn_map;
		typedef std::map<std::string, Channel>		channel_map;
		typedef std::map<std::string, Connexion*>	nick_map;
		typedef std::stack<Connexion*>				rm_list;


		// -- private members --------------------------------------------------

		bool			_initialized;
		ServerInfo		_info;
		Shared_fd		_socket;
		Poll			_poller;
		channel_map 	_channels;
		conn_map		_conns;
		nick_map		_nicks;
		rm_list			_rm_list;
		std::string		_motd;

};
static const char* message_irc = 
"This server has been sponsored by 935\r\n"
" \r\n"
"-------------------------------------------------------------------\r\n"
"[%] Server Staff =-\r\n"
" \r\n"
".::. Administrator....:\r\n"
"                        Maxis\r\n"
"\r\n"
".::. Operators........:\r\n"
"                        diroyer\r\n"
"                        tutur\r\n"
"                        momadani\r\n"
" \r\n"
"-------------------------------------------------------------------\r\n"
"[%] Server Policies =-\r\n"
" \r\n"
"a. No spamming or advertising allowed, if found you will be banned from this server/network.\r\n"
"b. No malicious bots, including flood and nick/channel chasers.\r\n"
"c. No channel filler bots/clients/psybncs.\r\n"
"   # A channel filler is a client, bnc, or bot which is connected just to fill a channel and make it look bigger.\r\n"
"d. Operator impersonation will not be tolerated and cause you to be banned from this server/network.\r\n"
" \r\n"
"\"REMEMBER IRC IS A PRIVILEGE, NOT A RIGHT\"\r\n"
"-------------------------------------------------------------------\r\n"
" \r\n"
"Thank you for using Backrooms.net, we hope you enjoy the stay with us.";

#endif
