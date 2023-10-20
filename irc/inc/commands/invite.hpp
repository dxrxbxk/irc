#ifndef INVITE_HPP
# define INVITE_HPP

# include "command.hpp"

class Invite : public Command {
	public:
		Invite(Connexion& c, Message& m);
		~Invite(void);

		ret_type execute(void);

		static Command* create(Connexion& c, Message& m);

	private:
};

#endif
