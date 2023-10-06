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
# include <map>

# include "connexion.hpp"
# include "logger.hpp"


class Channel {

	public:

		// -- public constructors ---------------------------------------------

		Channel(void);
		Channel(const std::string&, Connexion&);
		~Channel(void);
		Channel(const Channel&);
		Channel& operator=(const Channel&);

		void		change_admin(Connexion&);
		void		add_user(Connexion&);
		void		remove_user(Connexion&);
		void		broadcast(const std::string&, const Connexion&);
		std::size_t size(void) const;

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
		std::map<std::string, Connexion*>	_users;
		std::string							_modes[NB_MODES];
};

#endif
