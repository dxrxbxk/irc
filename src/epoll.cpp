/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 18:19:01 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 03:25:22 by diroyer          ###   ########.fr       */
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

	Logger::start();

	while (is_running == true) {

		// refresh logger print
		Logger::render();

		// wait for events
		const int nfds = epoll_wait(epollfd, v_events.data(), v_events.size(), -1);

		// check for errors
		if (nfds < 0 && errno != EINTR)
			throw std::runtime_error("epoll_wait");

		// loop over events
		for (int n = 0; n < nfds; ++n) {

			const uint32_t evnt = v_events[n].events;

			if (evnt & EPOLLIN) {
				IOEvent &ref = getEventData(v_events[n]);
				ref.read();
			}
			if (evnt & EPOLLOUT) {
				IOEvent &ref = getEventData(v_events[n]);
				ref.write();
			}
			if (evnt & EPOLLRDHUP || evnt & EPOLLHUP) {
				IOEvent &ref = getEventData(v_events[n]);
				delEvent(ref);
				ref.disconnect();
			}
		}

		// resize vector if needed
		if (static_cast<std::size_t>(nfds) > v_events.size())
			v_events.resize(nfds);

	}
	Logger::end();
}

IOEvent&	Poll::getEventData(epoll_event &ref) {
	return *static_cast<IOEvent *>(ref.data.ptr);
}

void	Poll::delEvent(IOEvent &ref) {
	if (epoll_ctl(epollfd, EPOLL_CTL_DEL, ref.fd(), NULL) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl"));
	v_events.resize(v_events.size() - 1);
}

void	Poll::addEvent(IOEvent &ref) {
	epoll_event ev;

	memset(&ev, 0, sizeof(epoll_event));
	ev.events = EPOLLIN | EPOLLRDHUP | EPOLLHUP;
	ev.data.ptr = &ref;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, ref.fd(), &ev) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl add"));
	v_events.resize(v_events.size() + 1);
}

void	Poll::modEvent(IOEvent &ref, int flag) {
	epoll_event	ev;

	memset(&ev, 0, sizeof(epoll_event));
	ev.events = flag | EPOLLRDHUP | EPOLLHUP;
	ev.data.ptr = &ref;

	if (epoll_ctl(epollfd, EPOLL_CTL_MOD, ref.fd(), &ev) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl mod"));
}
