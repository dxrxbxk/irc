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

// -- private constructors ----------------------------------------------------

Signal::Signal(void) {}

Signal::~Signal(void) {}

// -- private static methods --------------------------------------------------

Signal& Signal::shared(void) {
	static Signal signal;
	return signal;
}

void	Signal::signal_no_pipe(int) {
	// do nothing
}

// -- public static methods ---------------------------------------------------

void	Signal::signal_nopipe_manager(void) {
	// record signal handler
	if (::signal(SIGINT,  signal_no_pipe) == SIG_ERR
	 || ::signal(SIGABRT, signal_no_pipe) == SIG_ERR
	 || ::signal(SIGQUIT, signal_no_pipe) == SIG_ERR
	 || ::signal(SIGTERM, signal_no_pipe) == SIG_ERR
	 || ::signal(SIGTSTP, signal_no_pipe) == SIG_ERR)
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

void	Signal::signal_default(void) {
	// default signals
	if (::signal(SIGINT,  SIG_DFL) == SIG_ERR
	 || ::signal(SIGABRT, SIG_DFL) == SIG_ERR
	 || ::signal(SIGQUIT, SIG_DFL) == SIG_ERR
	 || ::signal(SIGTERM, SIG_DFL) == SIG_ERR
	 || ::signal(SIGTSTP, SIG_DFL) == SIG_ERR)
		throw std::runtime_error(handleSysError("signal"));
}
