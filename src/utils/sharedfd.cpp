/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sharedfd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:48:50 by diroyer           #+#    #+#             */
/*   Updated: 2023/08/21 23:48:15 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sharedfd.hpp"

Shared_fd::Shared_fd(void) : _fd(-1), _count(NULL) {}

Shared_fd::Shared_fd(const int fd)
: _fd(fd), _count(NULL) {

	if (_fd == -1)
		return;
	_count = new int(1);
}


Shared_fd::Shared_fd(const Shared_fd& other)
: _fd(other._fd), _count(other._count) {
		if (_fd != -1) {
			++(*_count);
		}
}

Shared_fd::operator int(void) const {
	return _fd;
}



Shared_fd& Shared_fd::operator=(const Shared_fd& other) {

	if (this != &other) {

		if (_fd != -1) {
			if (--(*_count) == 0) {
				delete _count;
				::close(_fd);
			}
		}

		_fd = other._fd;
		_count = other._count;
		if (_fd != -1)
			++(*_count);
	}

	return *this;
}

Shared_fd::~Shared_fd(void) {
	if (_fd != -1) {
		if (--(*_count) == 0) {
			delete _count;
			::close(_fd);
		}
	}
}
