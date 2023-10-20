#ifndef JOIN_HPP
# define JOIN_HPP

#include "command.hpp"

class Join : public Command {

	public:

		Join(Bot&, Message&);

		~Join(void);

		ret_type execute(void);

		static Command* create(Bot&, Message&);

	private:

};


#endif
