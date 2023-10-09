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
: _name(), _admin(), _topic(), _op_list(), _users(), _modes()
{
}

Channel::Channel(const std::string& channel_name, Connexion& creator)
: _name(channel_name),
	_admin(&creator),
	_topic(),
	_op_list(),
	_users(),
	_modes()
{
		add_user(creator);
		add_op(creator.nickname());
}

Channel::~Channel(void) {}

Channel::Channel(const Channel& other)
:	_name(other._name),
	_admin(other._admin),
	_topic(other._topic),
	_op_list(other._op_list),
	_users(other._users),
	_modes(other._modes)
{
}

Channel& Channel::operator=(const Channel& other) {
	if (this != &other) {
		   _name = other._name;
		  _admin = other._admin;
		  _topic = other._topic;
		_op_list = other._op_list;
		  _users = other._users;
		  _modes = other._modes;
	}
	return *this;
}

// -- public accessors modes --------------------------------------------------------

std::string&	Channel::name(void) {
	return _name;
}

void Channel::name(std::string& name) {
	_name.swap(name);
}

void	Channel::topic(std::string& topic) {
	_topic.swap(topic);
}

void	Channel::topic(const std::string& topic) {
	_topic = topic;
}

std::string&	Channel::topic(void) {
	return _topic;
}

void	Channel::topic(bool option) {
	_modes.topicRestrictions = option;
}

void	Channel::limit(int limit) {
	_modes.userLimit = limit;
}

int		Channel::limit(void) {
	return _modes.userLimit;
}

void	Channel::key(std::string& key) {
	_modes.channelKey.swap(key);
}

void	Channel::key(const std::string& key) {
	_modes.channelKey = key;
}

std::string&	Channel::key(void) {
	return _modes.channelKey;
}

void	Channel::key(bool option) {
	_modes.channelKey = option;
}

void	Channel::invite_only(bool option) {
	_modes.inviteOnly = option;
}

bool	Channel::invite_only(void) {
	return _modes.inviteOnly;
}

// -- public methods ----------------------------------------------------------

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

bool	Channel::user_in(std::string& user) const {
	return (_users.find(user) != _users.end());
}

bool	Channel::is_admin(Connexion& user) {
	return (&user == _admin);
}

void	Channel::add_op(std::string& user) {
	_op_list.push_back(user);
}

void	Channel::rm_op(std::string &op) {
	for (vec_str::iterator it = _op_list.begin(); it != _op_list.end(); ++it) {
		if (*it == op) {
			_op_list.erase(it);
			return ;
		}
	}
}	

bool	Channel::is_op(std::string& user) {
	for (vec_str::iterator it = _op_list.begin(); it != _op_list.end(); ++it) {
		if (*it == user)
			return true;
	}
	return false;
}
