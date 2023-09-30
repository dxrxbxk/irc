#include "command_factory.hpp"


CommandFactory::CommandFactory(void)
: cmap(init()) {}


CommandFactory::~CommandFactory(void) {}


CommandFactory::map_t CommandFactory::init(void) {
	map_t cmap;

	cmap["join"] = &Join::create;
	cmap["ping"] = &Ping::create;
	// add more commands here...

	return cmap;
}


CommandFactory& CommandFactory::shared(void) {
	static CommandFactory instance;
	return instance;
}


Command* CommandFactory::create(Connexion& conn, const Message& msg) {
	CommandFactory& factory = shared();

	map_t::const_iterator it = factory.cmap.find(msg.get_command());
	if (it == factory.cmap.end())
		return NULL;
	return it->second(conn, msg);
}
