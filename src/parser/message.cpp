/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:58:58 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 03:09:53 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "message.hpp"

Message::Message() : _middle() {
}

Message::~Message() {
}

void	Message::addPrefix(std::string& prefix) {
	_prefix.swap(prefix);
}

void	Message::addCommand(std::string& command) {
	_command.swap(command);
}

void	Message::addMiddle(std::string& middle) {
	_middle.push_back("");
	_middle.back().swap(middle);
}

void	Message::addTrailing(std::string& trailing) {
	_trailing.swap(trailing);
}


bool	Message::has_command(void) const {
	return !_command.empty();
}

bool	Message::has_prefix(void) const {
	return !_prefix.empty();
}

bool	Message::has_params(void) const {
	return !_middle.empty();
}

bool	Message::has_middle(void) const {
	return !_middle.empty();
}

bool	Message::has_trailing(void) const {
	return !_trailing.empty();
}


const std::string& Message::command(void) const {
	return _command;
}

std::string& Message::prefix(void) {
	return _prefix;
}

l_str&	Message::params(void) {
	return _middle;
}

std::string&	Message::params_first(void) {
	return _middle.front();
}

std::string&	Message::param(const std::size_t index) {
	return _middle[index];
}

std::string&	Message::trailing(void) {
	return _trailing;
}

std::size_t		Message::params_size(void) const {
	return _middle.size();
}


// debug
void Message::print(void) const {

	std::string msg;

	if (not _prefix.empty())
		msg.append("prefix " + _prefix);

	if (not _command.empty()) {
		if (not _prefix.empty())
			msg.append(" ");
		msg.append("command [" + _command + "]");
	}

	if (not _middle.empty()) {

		if (not _prefix.empty() or not _command.empty())
			msg.append(" ");
		msg.append("middle ");
		for (std::size_t i = 0; i < _middle.size(); i++)
			msg.append("[" + _middle[i] + "] ");
	}

	if (not _trailing.empty()) {
		msg.append("trailing [" + _trailing + "]");
	}

	Logger::info(msg);
}
