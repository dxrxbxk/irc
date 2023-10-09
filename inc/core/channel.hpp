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

# define MAX_CHANNEL_USER 10000
# define CHANNEL_KEY_SIZE 50
# define CHANNEL_NAME_SIZE 200

struct ModeInfo {
	bool			inviteOnly;
	bool			topicRestrictions;
	std::string		channelKey;
	bool			operatorPrivileges;
	int				userLimit;

	ModeInfo()
	:	inviteOnly(false),
		topicRestrictions(false), 
		channelKey(),
		operatorPrivileges(),
		userLimit(MAX_CHANNEL_USER)
	{};

	~ModeInfo() {};
};

class Channel {

	public:

		// -- public constructors ---------------------------------------------

		Channel(const std::string&, Connexion&);
		Channel(void);
		~Channel(void);
		Channel(const Channel&);
		Channel& operator=(const Channel&);

		// -- public accessors ---------------------------------------------
		
		void			add_user(Connexion&);
		void			remove_user(Connexion&);

		void			change_admin(Connexion&);
		bool			is_admin(Connexion&);

		void			add_op(std::string&);
		void			rm_op(std::string&);
		bool			is_op(std::string&);

		std::string&	name(void);
		void			name(std::string&);

		std::string&	topic(void);
		void			topic(std::string&);
		void			topic(const std::string&);
		void			topic(bool);
		bool			topic_resrict(void);

		void			limit(int);
		int				limit(void);

		void			key(std::string&);
		void			key(const std::string&);
		std::string&	key(void);
		void			key(bool);

		void			invite_only(bool);
		bool			invite_only(void);

		void			broadcast(const std::string&, const Connexion&);
		void			broadcast(const std::string&);

		bool			user_in(std::string& nickname) const ;
		std::size_t 	size(void) const;

	private:
		typedef std::map<std::string, Connexion*>::const_iterator	const_iterator;
		typedef std::vector<bool>									vec_bool;

		std::string							_name;
		Connexion*							_admin;
		std::string							_topic;
		vec_str								_op_list;
		std::map<std::string, Connexion*>	_users;
		ModeInfo							_modes;
};

#endif
