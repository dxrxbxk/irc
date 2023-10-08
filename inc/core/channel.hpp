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

struct ModeInfo {
	bool		inviteOnly;
	bool		topicRestrictions;
	std::string	channelKey;
	bool		operatorPrivileges;
	int			userLimit;

	ModeInfo()
	: inviteOnly(), topicRestrictions(), channelKey(), operatorPrivileges(), userLimit() {};

	~ModeInfo() {};
};

class Channel {

	public:

		// -- public constructors ---------------------------------------------

		Channel(void);
		Channel(const std::string&, Connexion&);
		~Channel(void);
		Channel(const Channel&);
		Channel& operator=(const Channel&);

		// -- public accessors ---------------------------------------------
		
		void			change_admin(Connexion&);
		void			add_user(Connexion&);
		void			remove_user(Connexion&);
		void			broadcast(const std::string&, const Connexion&);
		std::size_t 	size(void) const;

		bool			inviteOnly(void);
		void			inviteOnly(bool option);

		bool			topicRestrictions(void);
		void			topicRestrictions(bool option);

		std::string&	channelKey(void);
		void			channelKey(std::string&);

		bool			operatorPrivileges(void);
		void			operatorPrivileges(bool option);

		int				userLimit(void);
		void			userLimit(int option);




	private:
		typedef std::map<std::string, Connexion*>::const_iterator const_iterator;
		typedef std::vector<bool> vec_bool;

		std::string							_name;
		Connexion*							_admin;
		std::string							_topic;
		vec_str								_op_list;
		std::map<std::string, Connexion*>	_users;
		ModeInfo							_modes;
};

#endif
