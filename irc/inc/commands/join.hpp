#ifndef JOIN_HPP
# define JOIN_HPP

#include "command.hpp"
#include "types.hpp"

class Join : public Command {

	public:

		Join(Connexion&, Message&);

		~Join(void);

		ret_type execute(void);

		static Command* create(Connexion&, Message&);

	private:

		bool		valid_channel(std::string const&) const;
		void		split_channel(std::string const&);
		void		split_keys(std::string const&);
		vec_str		_channels;
		vec_str		_keys;
};

#endif
