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
#include "utils.hpp"


Poll::Poll(void)
: _instance(::epoll_create(1)), _events() , _running(true) {

	_events.reserve(DEFAULT_EVENTS);

	if (_instance == -1)
		throw std::runtime_error(handleSysError("epoll_create"));
	else
		std::cout << "epoll instance: " << _instance << std::endl;
}

Poll::~Poll(void) {
	if (_instance != -1)
		::close(_instance);
	Logger::end();
}

void Poll::stop(void) {
	_running = false;
}

int		Poll::check(const int nfds) {
#if defined PIPE
	if (nfds < 0) {
		if (errno != EINTR)
			return -1;
	}
	else {
		if (static_cast<size_type>(nfds) == _events.size())
			_events.resize(nfds);
	}
#else
	if (nfds < 0)
		return -1;
	else {
		if (static_cast<size_type>(nfds) == _events.size())
			_events.resize(nfds);
	}
#endif
	return 0;
}

void Poll::run(void) {

	const int nfds = ::epoll_wait(_instance, _events.data(), _events.size(), -1);

	if (check(nfds) == -1)
		throw std::runtime_error(handleSysError("epoll_wait"));

	for (int n = 0; n < nfds; ++n) {

		const uint32_t event = _events[n].events;
		IOEvent& io          = data(_events[n]);

		if (event & EPOLLRDHUP || event & EPOLLHUP) {
			Logger::info("epoll HUP");
			io.disconnect();
		}
		else if (event & EPOLLIN) {
			Logger::info("epoll IN");
			io.read();
		}
		else if (event & EPOLLOUT) {
			Logger::info("epoll OUT");
			io.write();
		}
	}
}

IOEvent& Poll::data(epoll_event& event) {
	return *static_cast<IOEvent*>(event.data.ptr);
}

void Poll::del_event(const IOEvent& io) {
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
