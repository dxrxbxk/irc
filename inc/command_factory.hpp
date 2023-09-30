#ifndef COMMAND_FACTORY_HPP
# define COMMAND_FACTORY_HPP

# include <map>
# include <string>

// # include "connexion.hpp"
class Connexion;
# include "message.hpp"
# include "join.hpp"
# include "command.hpp"



class CommandFactory {

	public:

		typedef Command* (*cmd_t)(Connexion&, const Message&);

		typedef std::map<std::string, cmd_t> map_t;

		static Command* create(Connexion&, const Message&);


	private:

		CommandFactory();
		~CommandFactory();

		static map_t init(void);

		static const map_t cmap;

};



#endif
