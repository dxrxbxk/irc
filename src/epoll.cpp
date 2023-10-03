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


Poll::Poll(void)
: _instance(::epoll_create(1)), _events() , _running(true) {

	_events.reserve(DEFAULT_EVENTS);

	if (_instance == -1)
		throw std::runtime_error(handleSysError("epoll_create"));

}

Poll::~Poll(void) {
	if (_instance != -1)
		::close(_instance);
	Logger::end();
}

void Poll::stop(void) {
	_running = false;
}

void Poll::run(void) {

	Logger::start();

	while (_running == true) {

		// refresh logger print
		Logger::render();

		// wait for events
		const int nfds = ::epoll_wait(_instance, _events.data(), _events.size(), -1);

		// check for errors
		if (nfds < 0 && errno != EINTR)
			throw std::runtime_error("epoll_wait");

		// loop over events
		for (int n = 0; n < nfds; ++n) {

			const uint32_t event = _events[n].events;
			IOEvent& io          = data(_events[n]);

			if (event & EPOLLIN)
				io.read();

			if (event & EPOLLOUT)
				io.write();

			if (event & EPOLLRDHUP || event & EPOLLHUP) {
				del_event(io); io.disconnect();
			}
		}

		// resize vector if needed
		if (static_cast<std::size_t>(nfds) > _events.size())
			_events.resize(nfds);

	}
	Logger::end();
}


IOEvent& Poll::data(epoll_event& event) {
	return *static_cast<IOEvent*>(event.data.ptr);
}

void Poll::del_event(IOEvent& io) {
	if (::epoll_ctl(_instance, EPOLL_CTL_DEL, io.fd(), NULL) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl"));
	_events.pop_back();
}


void Poll::add_event(IOEvent& io) {

	setnonblocking(io.fd());

	epoll_event ev = new_event(io, EPOLLIN);

	if (::epoll_ctl(_instance, EPOLL_CTL_ADD, io.fd(), &ev) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl add"));
	_events.resize(_events.size() + 1);
}

void Poll::mod_event(IOEvent& io, int flag) {

	epoll_event ev = new_event(io, flag);

	if (::epoll_ctl(_instance, EPOLL_CTL_MOD, io.fd(), &ev) == -1)
		throw std::runtime_error(handleSysError("epoll_ctl mod"));
}

Poll::epoll_event Poll::new_event(IOEvent& io, const int flags) {
	epoll_event	ev;
	std::memset(&ev, 0, sizeof(epoll_event));
	ev.events   = flags | EPOLLRDHUP | EPOLLHUP;
	ev.data.ptr = &io;
	return ev;
}
