#ifndef JOIN_HPP
# define JOIN_HPP

#include "command.hpp"

class Join : public Command {

	public:

		Join(Connexion&, Message&);

		~Join(void);

		ret_type execute(void);

		static Command* create(Connexion&, Message&);

	private:

};

#endif
