#include "topic.hpp"
#include "server.hpp"
#include "channel.hpp"

Topic::Topic(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Topic::~Topic(void) {}

Command::ret_type	Topic::execute(void) {
	std::string& target = _msg.params()[0];
	std::string& topic = _msg.trailing();
	Channel& channel = Server::shared().channel(target);
	return 0;
}

Command* Topic::create(Connexion& conn, Message& msg) {
	return new Mode(conn, msg);
}
