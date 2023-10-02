#include "ping.hpp"
#include "server.hpp"


#define HINT(CMD, ACTION) std::cout \
	<< "\x1b[32m" \
	<< CMD \
	<< ":\x1b[0m " \
	<< ACTION << std::endl


Ping::Ping(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Ping::~Ping(void) {}

bool Ping::evaluate(void) {
	if (_msg.get_middle_size() < 1)
		return false;// ERR_NOORIGIN
	return true;
}

void Ping::execute(void) {
	_server.response(_conn, "PONG :" + _msg.get_middle(0));
}

Command* Ping::create(Connexion& conn, Message& msg) {
	return new Ping(conn, msg);
}

