/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:19:01 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/27 16:14:59 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "epoll.hpp"

const Poll::size_type Poll::DEFAULT_SIZE = 10;

Poll::Poll() : v_events() , is_running(true) {
	v_events.reserve(DEFAULT_SIZE);

	epollfd = epoll_create(1);
	if (epollfd == -1)
		throw std::runtime_error(handleSysError("epoll_create"));
}

Poll::~Poll() {
	if (epollfd != -1)
		close(epollfd);
}

void	Poll::stop(void) {
	this->is_running = false;
	std::cout << "Poll::disconnect" << std::endl;
}

void	Poll::run(void) {
	epollWait();
}

void	Poll::epollWait(void) {
	int		nfds;

	nfds = -1;
	while (is_running) {
		nfds = epoll_wait(epollfd, v_events.data(), v_events.size(), -1);
		if (nfds == -1 && errno != EINTR) 
			throw std::runtime_error("epoll_wait");
		else if (nfds > 0) {
			for (int n = 0; n < nfds; ++n) {
				if (v_events[n].events & EPOLLIN) {
					notification &ref = getEventData(v_events[n]);
					ref.notify();
				}
				if (v_events[n].events & EPOLLRDHUP) {
					notification &ref = getEventData(v_events[n]);
					delEvent(ref);
					ref.disconnect();
				}	
			}
		}
	}
}

notification&	Poll::getEventData(epoll_event &ref) {
	return *static_cast<notification *>(ref.data.ptr);
}

void	Poll::delEvent(notification &ref) {
	if (epoll_ctl(epollfd, EPOLL_CTL_DEL, ref.getFd(), NULL) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl"));
	v_events.resize(v_events.size() - 1);
}

void	Poll::addEvent(notification &ref) {
	epoll_event ev;
	std::cout << "Adding new event for " << ref.getFd() << std::endl;

	memset(&ev, 0, sizeof(epoll_event));
	ev.events = EPOLLIN | EPOLLRDHUP;
	ev.data.ptr = &ref;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, ref.getFd(), &ev) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl"));
	v_events.resize(v_events.size() + 1);
}