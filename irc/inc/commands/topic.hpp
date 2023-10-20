#ifndef TOPIC_HPP
# define TOPIC_HPP

# include "command.hpp"

class Topic : public Command {

	public:

		Topic(Connexion&, Message&);
		~Topic(void);

		ret_type execute(void);

		static Command* create(Connexion&, Message&);

	private:

};

#endif
