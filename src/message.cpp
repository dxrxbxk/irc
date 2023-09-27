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
