#include "command_factory.hpp"


CommandFactory::CommandFactory(void)
: cmap(init()) {}


CommandFactory::~CommandFactory(void) {}

CommandFactory::map_t CommandFactory::init(void) {
	map_t cmap;

	cmap[":hello"]     = &Hello::create;
	return cmap;
}


CommandFactory& CommandFactory::shared(void) {
	static CommandFactory instance;
	return instance;
}


Command* CommandFactory::create(Bot& conn, Message& msg) {
	CommandFactory& factory = shared();

	map_t::const_iterator it = factory.cmap.find(msg.trailing());
	if (it == factory.cmap.end())
		return NULL;
	return it->second(conn, msg);
}
