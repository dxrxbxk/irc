/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 00:44:14 by diroyer           #+#    #+#             */
/*   Updated: 2023/10/02 03:57:14 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <vector>
# include <string>
# include "connexion.hpp"


class Channel {
	public:
		Channel();
		Channel(std::string name, Connexion&);
		~Channel();
		Channel(const Channel&);
		Channel& operator=(const Channel&);

		void	change_admin(Connexion& old);
		void	add_user(Connexion &new_user);
		void	send_msg(const std::string msg);

		enum mode {
			INVITATION,
			TOPIC,
			KEY,
			OPERATOR,
			USER_LIMIT,
			NB_MODES
		};
	private:
		typedef std::map<std::string, Connexion*>::const_iterator const_iterator;

		std::string							_name;
		Connexion*							_admin;
		std::string							_topic;
		vec_str								_op_list;
		std::string							_modes[NB_MODES];
		std::map<std::string, Connexion*>	_users;
};

#endif
