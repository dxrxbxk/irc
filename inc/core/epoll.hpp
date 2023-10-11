/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:19:20 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 02:23:56 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EPOLL_HPP
# define EPOLL_HPP

# include <sys/epoll.h>
# include <vector>
# include <iostream>
# include <unistd.h>
# include <cerrno>
# include <cstring>
# include <cstdio>

# include "io_event.hpp"
# include "signal.hpp"
# include "utils.hpp"
# include "connexion.hpp"
# include "logger.hpp"
# include "utils.hpp"

class Server;

class Poll {

	public:

		Poll(void);
		~Poll(void);

		void	add_event(IOEvent&, int);
		void	add_event(IOEvent&);
		void	mod_event(IOEvent&, int);
		void	del_event(const IOEvent&);
		void	run(void);
		void	stop(void);
		void	check(const int);


	private:
		typedef struct epoll_event 			epoll_event;
		typedef std::vector<epoll_event>	vector_event;
		typedef vector_event::size_type		size_type;

		static const size_type				DEFAULT_SIZE;
		enum { DEFAULT_EVENTS = 10 };

		int									_instance;
		vector_event 						_events;
		bool								_running;
		int									_listen_fd;

		IOEvent&							data(epoll_event &ref);
		epoll_event							new_event(IOEvent& ref, const int flags);
};

#endif
