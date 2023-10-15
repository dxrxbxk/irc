#ifndef INVITE_HPP
# define INVITE_HPP

#include "command.hpp"

class Invite : public Command {

	public:

		Invite(Bot&, Message&);

		~Invite(void);

		ret_type execute(void);

		static Command* create(Bot&, Message&);

	private:

};


#endif
