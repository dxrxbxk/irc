#ifndef PART_HPP
# define PART_HPP

# include "command.hpp"

class Part : public Command {
	public:

		Part(Connexion&, Message&);
		~Part(void);

		ret_type execute(void);

		static Command* create(Connexion&, Message&);

	private:


};

#endif
