#ifndef PING_HPP
# define PING_HPP


#include "command.hpp"


class Ping : public Command {

	public:

		Ping(Connexion&, const Message&);

		~Ping(void);

		bool evaluate(void);

		void execute(void);

		static Command* create(Connexion&, const Message&);

	private:

};




#endif
