#ifndef CAP_HPP 
# define CAP_HPP

#include "command.hpp"

class Cap : public Command {

	public:

		Cap(Connexion&, Message&);

		~Cap(void);

		SendInfo execute(void);

		static Command* create(Connexion&, Message&);

	private:

};

#endif
