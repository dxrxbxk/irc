/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 20:55:24 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 19:40:17 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal.hpp"

void	Signal::disconnect(void) {
}

void	signalHandler(int signum) {
	(void)signum;
	char c = 0;
	write(g_signalPipe[1], &c, sizeof(c));
}

void	signalManager(void) {
	if (signal(SIGINT, signalHandler) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
	if (signal(SIGABRT, signalHandler) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
	if (signal(SIGQUIT, signalHandler) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
	if (signal(SIGTERM, signalHandler) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
	if (signal(SIGTSTP, signalHandler) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
}

void	signalIgnore(void) {
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
	if (signal(SIGABRT, SIG_IGN) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
	if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
	if (signal(SIGTSTP, SIG_IGN) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
}

Signal::Signal() {
	std::cout << "Pipe constructor called" << std::endl;
	g_signalPipe[0] = -1;
	g_signalPipe[1] = -1;
	if (pipe(g_signalPipe) == -1)
		throw std::runtime_error(handleSysError("pipe"));
}

Signal::~Signal() {
	std::cout << "Pipe destructor called" << std::endl;
	closeFd(g_signalPipe[0]);
	closeFd(g_signalPipe[1]);
}

int		Signal::getFd(void) const {
	return (g_signalPipe[0]);
}

void	Signal::read(void) {
	char c;

	std::cout << "Signal read" << std::endl;
	if (::read(g_signalPipe[0], &c, sizeof(c)) == -1)
		ERROR(handleSysError("pipe read"));
	throw std::runtime_error("Signal: Interrupted system call");
}
