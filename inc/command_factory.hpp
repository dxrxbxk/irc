#ifndef COMMAND_FACTORY_HPP
# define COMMAND_FACTORY_HPP

# include <map>
# include <string>

# include "message.hpp"
# include "command.hpp"
# include "join.hpp"
# include "ping.hpp"


class Connexion;

class CommandFactory {

	public:

		typedef Command* (*cmd_t)(Connexion&, const Message&);

		typedef std::map<std::string, cmd_t> map_t;

		static Command* create(Connexion&, const Message&);


	private:

		static CommandFactory& shared(void);

		CommandFactory(void);
		~CommandFactory(void);

		static map_t init(void);





		const map_t cmap;

};



#endif
