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

Channel::Channel() {
}

void	Channel::change_admin(Connexion& old) {
	_admin = &old;
}

void	Channel::send_msg(std::string msg) {
	for (const_iterator it = _users.begin(); it != _users.end(); ++it) {
		if (send(it->second->getFd(), msg.c_str(), msg.size(), 0) == -1) {
		}
	}
}

Channel::Channel(const std::string channel_name, Connexion& creator)
: _name(channel_name), _admin(&creator) {
	add_user(creator);
}

void	Channel::add_user(Connexion &new_user) {
	std::string	nickname = new_user.get_nickname();	
	_users[nickname] = &new_user;
}

Channel::~Channel() {} 

Channel::Channel(const Channel& copy) { *this = copy; }

Channel& Channel::operator=(const Channel& copy) {
	if (this != &copy) {
		_name = copy._name;
		_admin = copy._admin;
		_topic = copy._topic;
		_op_list = copy._op_list;
	
		for (std::size_t i = 0; i < NB_MODES; ++i) {
			_modes[i] = copy._modes[i];
		}
		_users = copy._users;
	}
	return *this;
}

