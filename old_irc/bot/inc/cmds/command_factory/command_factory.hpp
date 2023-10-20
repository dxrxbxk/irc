#ifndef COMMAND_FACTORY_HPP
# define COMMAND_FACTORY_HPP

# include <map>
# include <string>

# include "message.hpp"
# include "command.hpp"
# include "utils.hpp"

# include "hello.hpp"
# include "join.hpp"
# include "part.hpp"
# include "joke.hpp"
# include "invite.hpp"

class Bot;

class CommandFactory {

	public:

		typedef Command* (*cmd_t)(Bot&, Message&);

		typedef std::map<std::string, cmd_t> map_t;

		static Command* create(Bot&, Message&);

	private:

		static CommandFactory& shared(void);

		CommandFactory(void);
		~CommandFactory(void);

		static map_t init(void);

		map_t cmap;

};



#endif
