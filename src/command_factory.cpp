#include "command_factory.hpp"


CommandFactory::CommandFactory() {}

CommandFactory::~CommandFactory() {}


CommandFactory::map_t CommandFactory::init(void) {
	map_t cmap;

	// cmap["join"] = &Join::create;
	// add more commands here...

	return cmap;
}

const CommandFactory::map_t CommandFactory::cmap = CommandFactory::init();


Command* CommandFactory::create(Connexion& conn, const Message& msg) {
	map_t::const_iterator it = cmap.find(msg.get_command());
	if (it == cmap.end())
		return NULL;


	return it->second(conn, msg);
}
