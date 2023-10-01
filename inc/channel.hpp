/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:44:14 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 01:47:43 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <string>
# include "types.hpp"

class Channel {
	public:
		Channel(const std::string name);
		~Channel();

		enum mode {
			INVITATION,
			TOPIC,
			KEY,
			OPERATOR,
			USER_LIMIT,
			NB_MODES
		};
	private:
		Channel();

		std::string	_name;
		std::string	_topic;
		vec_str		_user_list;
		vec_str		_op_list;
		std::string	_modes[NB_MODES];
};

#endif
