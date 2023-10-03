#ifndef PRIVMSG_HPP
# define PRIVMSG_HPP


#include "command.hpp"

class Privmsg : public Command {

	public:

		Privmsg(Connexion&, Message&);

		~Privmsg(void);

		void execute(void);

		static Command* create(Connexion&, Message&);

	private:

};




#endif
