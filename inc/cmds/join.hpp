#ifndef JOIN_HPP
# define JOIN_HPP

#include "command.hpp"

class Join : public Command {

	public:

		Join(Connexion&, Message&);

		~Join(void);

		bool evaluate(void);

		void execute(void);

		static Command* create(Connexion&, Message&);

	private:
		void	add_user_to_channel(void);

};

#endif
