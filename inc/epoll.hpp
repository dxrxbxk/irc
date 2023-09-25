/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:19:20 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/21 20:28:34 by diroyer          ###   ########.fr       */
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

# include "notification.hpp"
# include "signal.hpp"
# include "utils.hpp"
# include "connexion.hpp"

class Poll {
	public:
		Poll();
		~Poll();

		void	addEvent(notification &ref);
		void	delEvent(notification &ref);
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
		notification&						getEventData(epoll_event &ref);
};

#endif
