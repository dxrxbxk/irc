
#ifndef PASS_HPP
# define PASS_HPP

# include "command.hpp"

class Pass : public Command {

	public:

		Pass(Connexion&, Message&);

		~Pass(void);

		ret_type execute(void);

		static Command* create(Connexion&, Message&);

	private:

		int		check_password(const std::string&);

};

#endif
