/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:58:20 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/01 18:29:15 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include "types.hpp"
# include "logger.hpp"
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
		bool	has_prefix(void) const;
		bool	has_middle(void) const;
		bool	has_params(void) const;
		bool	has_trailing(void) const;

		const std::string&	get_command(void) const;
		std::string&	get_prefix(void);
		l_str&			get_middle(void);
		std::string&	get_middle(size_t index);
		std::size_t		get_middle_size() const;
		std::string&	get_trailing(void);

	private:

		std::string	_prefix;
		std::string	_command;

		l_str		_middle;
		std::string	_trailing;
};

#endif
