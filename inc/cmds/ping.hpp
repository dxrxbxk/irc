#ifndef PING_HPP
# define PING_HPP


#include "command.hpp"


class Ping : public Command {

	public:

		Ping(Connexion&, Message&);

		~Ping(void);

		void execute(void);

		static Command* create(Connexion&, Message&);

	private:

};




#endif
