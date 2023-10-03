/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:19:01 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 02:19:40 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "epoll.hpp"
#include "server.hpp"

const Poll::size_type Poll::DEFAULT_SIZE = 10;

Poll::Poll(void)
: v_events() , is_running(true) {
	v_events.reserve(DEFAULT_SIZE);

	epollfd = epoll_create(1);
	if (epollfd == -1)
		throw std::runtime_error(handleSysError("epoll_create"));

	addEvent(Logger::shared());
}

Poll::~Poll() {
	if (epollfd != -1)
		close(epollfd);
	Logger::end();
}

void Poll::stop(void) {
	this->is_running = false;
}

void Poll::run(void) {
	epollWait();
}

void	Poll::epollWait(void) {
	int		nfds;


	Logger::start();

	nfds = -1;
	while (is_running == true) {

		Logger::render();

		nfds = epoll_wait(epollfd, v_events.data(), v_events.size(), -1);

		if (nfds == -1 && errno != EINTR)
			throw std::runtime_error("epoll_wait");

		else if (nfds > 0) {
			for (int n = 0; n < nfds; ++n) {
				if (v_events[n].events & EPOLLIN) {
					IOEvent &ref = getEventData(v_events[n]);
					ref.read();
				}
				if (v_events[n].events & EPOLLOUT) {
					IOEvent &ref = getEventData(v_events[n]);
					ref.write();
				}
				if (v_events[n].events & EPOLLRDHUP || v_events[n].events & EPOLLHUP) {
					IOEvent &ref = getEventData(v_events[n]);
					delEvent(ref);
					ref.disconnect();
				}
			}
		}
	}
	Logger::end();
}

IOEvent&	Poll::getEventData(epoll_event &ref) {
	return *static_cast<IOEvent *>(ref.data.ptr);
}

void	Poll::delEvent(IOEvent &ref) {
	if (epoll_ctl(epollfd, EPOLL_CTL_DEL, ref.getFd(), NULL) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl"));
	v_events.resize(v_events.size() - 1);
}

void	Poll::addEvent(IOEvent &ref) {
	epoll_event ev;
	std::cout << "Adding new event for " << ref.getFd() << std::endl;

	memset(&ev, 0, sizeof(epoll_event));
	ev.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP;
	ev.data.ptr = &ref;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, ref.getFd(), &ev) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl add"));
	v_events.resize(v_events.size() + 1);
}

void	Poll::modEvent(IOEvent &ref, int flag) {
	epoll_event	ev;
	std::cout << "Moding event for " << ref.getFd() << std::endl;

	memset(&ev, 0, sizeof(epoll_event));
	ev.events |= flag;
	ev.data.ptr = &ref;

	if (epoll_ctl(epollfd, EPOLL_CTL_MOD, ref.getFd(), &ev) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl mod"));
}
