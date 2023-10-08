
#ifndef QUIT_HPP
# define QUIT_HPP

#include "command.hpp"

class Quit : public Command {

	public:

		Quit(Connexion&, Message&);
		~Quit(void);

		ret_type execute(void);

		static Command* create(Connexion&, Message&);

	private:

		bool	valid_mode(char c);

};

#endif
