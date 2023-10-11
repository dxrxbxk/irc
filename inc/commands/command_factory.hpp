#ifndef COMMAND_FACTORY_HPP
# define COMMAND_FACTORY_HPP

# include <map>
# include <string>

# include "message.hpp"
# include "command.hpp"
# include "join.hpp"
# include "ping.hpp"
# include "cap.hpp"
# include "nick.hpp"
# include "user.hpp"
# include "mode.hpp"
# include "privmsg.hpp"
# include "pass.hpp"
# include "quit.hpp"
# include "topic.hpp"
# include "kick.hpp"
# include "invite.hpp"

class Connexion;

class CommandFactory {

	public:

		typedef Command* (*cmd_t)(Connexion&, Message&);

		typedef std::map<std::string, cmd_t> map_t;

		static Command* create(Connexion&, Message&);


	private:

		static CommandFactory& shared(void);

		CommandFactory(void);
		~CommandFactory(void);

		static map_t init(void);

		map_t cmap;

};



#endif
