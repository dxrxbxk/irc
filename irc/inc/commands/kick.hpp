#ifndef KICK_HPP
# define KICK_HPP

# include "command.hpp"

class Kick : public Command {

	public:

		Kick(Connexion&, Message&);
		~Kick(void);

		ret_type execute(void);

		static Command* create(Connexion&, Message&);

	private:

};

#endif
