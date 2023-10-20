#ifndef JOKE_HPP
# define JOKE_HPP

#include "command.hpp"

class Joke : public Command {

	public:

		Joke(Bot&, Message&);

		~Joke(void);

		ret_type execute(void);

		static Command* create(Bot&, Message&);

	private:

};


#endif
