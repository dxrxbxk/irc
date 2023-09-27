/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:58:58 by diroyer           #+#    #+#             */
/*   Updated: 2023/09/27 16:31:45 by diroyer          ###   ########.fr       */
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

const std::string& Message::get_command(void) const {
	return _command;
}


// debug
void Message::print(void) const {

	std::cout << "prefix: " << _prefix << std::endl;
	std::cout << "command: " << _command << std::endl;
	std::cout << "middle: ";
	for (l_str::const_iterator it = _middle.begin(); it != _middle.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "trailing: " << _trailing << std::endl;
}





