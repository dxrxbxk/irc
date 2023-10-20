#ifndef HELLO_HPP
# define HELLO_HPP

#include "command.hpp"

class Hello : public Command {

	public:

		Hello(Bot&, Message&);

		~Hello(void);

		ret_type execute(void);

		static Command* create(Bot&, Message&);

	private:

};


#endif
