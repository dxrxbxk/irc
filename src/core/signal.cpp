/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:55:24 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/03 00:50:55 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.hpp"
#include "server.hpp"


// -- private constructors ----------------------------------------------------

Signal::Signal(void)
: _pipe() {
	// init pipe
	_pipe[0] = -1; _pipe[1] = -1;
	// // create pipe
	if (::pipe(_pipe) == -1)
		throw std::runtime_error(handleSysError("pipe"));
	else {
		std::cout << "pipe read end: " << _pipe[0] << std::endl;
		std::cout << "pipe write end: " << _pipe[1] << std::endl;
	}
}

Signal::~Signal(void) {
	// close pipe
	if (_pipe[0] != -1) ::close(_pipe[0]);
	if (_pipe[1] != -1) ::close(_pipe[1]);
}


// -- private static methods --------------------------------------------------

Signal& Signal::shared(void) {
	static Signal signal;
	return signal;
}

void Signal::signal_handler(int) {
	const char c = 0;
	::write(shared()._pipe[1], &c, sizeof(c));
}


// -- public static methods ---------------------------------------------------

void Signal::signal_manager(void) {
	// record signal handler
	if (::signal(SIGINT,  signal_handler) == SIG_ERR
	 || ::signal(SIGABRT, signal_handler) == SIG_ERR
	 || ::signal(SIGQUIT, signal_handler) == SIG_ERR
	 || ::signal(SIGTERM, signal_handler) == SIG_ERR
	 || ::signal(SIGTSTP, signal_handler) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
}

void Signal::signal_ignore(void) {
	// ignore signals
	if (::signal(SIGINT,  SIG_IGN) == SIG_ERR
	 || ::signal(SIGABRT, SIG_IGN) == SIG_ERR
	 || ::signal(SIGQUIT, SIG_IGN) == SIG_ERR
	 || ::signal(SIGTERM, SIG_IGN) == SIG_ERR
	 || ::signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
}


// -- public IOEvent interface ------------------------------------------------

void Signal::read(void) {
	char c;
	if (::read(_pipe[0], &c, sizeof(c)) == -1)
		throw std::runtime_error(handleSysError("pipe read"));
	Server::shared().stop();
}

int Signal::fd(void) const {
	return _pipe[0];
}

void Signal::write(void) {}

void Signal::disconnect(void) {}

