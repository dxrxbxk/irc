/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:19:20 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:37:22 by diroyer          ###   ########.fr       */
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

class Server;

class Poll {

	public:

		Poll(void);
		~Poll(void);

		void	addEvent(IOEvent &ref);
		void	modEvent(IOEvent &ref);
		void	delEvent(IOEvent &ref);
		void	run(void);
		void	stop(void);

	private:
		typedef struct epoll_event 			epoll_event;
		typedef std::vector<epoll_event>	vector_event;
		typedef vector_event::size_type		size_type;

		static const size_type				DEFAULT_SIZE;
		vector_event 						v_events;
//		size_type							index;
		int									epollfd;
		bool								is_running;

		void 								epollWait(void);
		IOEvent&							getEventData(epoll_event &ref);
};

#endif
