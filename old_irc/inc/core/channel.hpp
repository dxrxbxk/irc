#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <cstddef>
# include <vector>
# include <string>
# include <map>

# include "connexion.hpp"
# include "logger.hpp"
#include "types.hpp"

# define MAX_USER_PER_CHAN 10000
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
		userLimit(MAX_USER_PER_CHAN)
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
		void			rm_user_and_channel(Connexion&);
		void			print_users(void) const;


		void			change_admin(Connexion&);
		bool			is_admin(Connexion&);

		void			add_op(const std::string&);
		void			rm_op(const std::string&);
		bool			is_op(const std::string&);
		std::size_t		op_size(void) const;

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
		//void			key(bool);
		bool			has_key(void);

		void			invite_only(bool);
		bool			invite_only(void);

		void			invite(const std::string&);
		bool			is_invited(const std::string&);
		void			rm_invite(const std::string&);

		void			broadcast(const std::string&, const Connexion&);
		void			broadcast(const std::string&);

		bool			user_in(const std::string& nickname) const ;
		std::size_t 	size(void) const;

	private:
		typedef std::map<std::string, Connexion*>::const_iterator	const_iterator;

		std::string							_name;
		Connexion*							_admin;
		std::string							_topic;
		vec_str								_op_list;
		std::map<std::string, Connexion*>	_users;
		ModeInfo							_modes;
		list_str							_invite_list;
};

#endif
