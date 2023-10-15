#include "command_factory.hpp"


CommandFactory::CommandFactory(void)
: cmap(init()) {}


CommandFactory::~CommandFactory(void) {}

CommandFactory::map_t CommandFactory::init(void) {
	map_t cmap;

	cmap["hello"]     = &Hello::create;
	cmap["join"]      = &Join::create;
	cmap["joke"]      = &Joke::create;
	cmap["leave"]     = &Part::create;
	return cmap;
}


CommandFactory& CommandFactory::shared(void) {
	static CommandFactory instance;
	return instance;
}


Command* CommandFactory::create(Bot& conn, Message& msg) {
	CommandFactory& factory = shared();

	if (!msg.has_trailing())
		return NULL;
	std::string command = msg.trailing_first();

	map_t::const_iterator it = factory.cmap.find(command);
	if (it == factory.cmap.end())
		return NULL;
	return it->second(conn, msg);
}
