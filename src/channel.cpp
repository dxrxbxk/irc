/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:43:43 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 04:00:54 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "channel.hpp"

Channel::Channel(void)
: _name(), _admin(), _topic(), _op_list(), _users(), _modes() {
}

Channel::Channel(const std::string& channel_name, Connexion& creator)
: _name(channel_name), _admin(&creator), _topic(), _op_list(), _users(), _modes() {
	// add_user(creator);
}

Channel::~Channel(void) {}

Channel::Channel(const Channel& other)
:	_name(other._name),
	_admin(other._admin),
	_topic(other._topic),
	_op_list(other._op_list),
	_users(other._users),
	_modes() {

	for (std::size_t i = 0; i < NB_MODES; ++i)
		_modes[i] = other._modes[i];
}


Channel& Channel::operator=(const Channel& other) {
	if (this != &other) {
		   _name = other._name;
		  _admin = other._admin;
		  _topic = other._topic;
		_op_list = other._op_list;
		  _users = other._users;

		for (std::size_t i = 0; i < NB_MODES; ++i)
			_modes[i] = other._modes[i];
	}
	return *this;
}


void	Channel::change_admin(Connexion& old) {
	_admin = &old;
}

void	Channel::broadcast(const std::string& msg, const Connexion& sender) {
	Logger::debug("BROADCAST");
	for (const_iterator it = _users.begin(); it != _users.end(); ++it) {
		if (it->second != &sender) {
			it->second->enqueue(msg);
		}
	}
}

std::size_t Channel::size(void) const {
	return _users.size();
}

void Channel::add_user(Connexion& user) {
	_users[user.nickname()] = &user;
}

void	Channel::remove_user(Connexion& user) {
	_users.erase(user.nickname());
}

