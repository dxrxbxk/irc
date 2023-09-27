/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:58:20 by diroyer           #+#    #+#             */
/*   Updated: 2023/09/27 16:36:38 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "types.hpp"
# include <iostream>

class Message {
	public:
		Message();
		~Message();

		void	addPrefix(std::string& prefix);
		void	addCommand(std::string& command);
		void	addMiddle(std::string& middle);
		void	addTrailing(std::string& trailing);

		void	print(void) const;

		bool	has_command(void) const;
		const std::string& get_command(void) const;

	private:
		std::string	_prefix;
		std::string	_command;

		l_str		_middle;
		std::string	_trailing;
};

#endif
