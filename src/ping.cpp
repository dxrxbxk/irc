#include "ping.hpp"
#include "server.hpp"


#define HINT(CMD, ACTION) std::cout \
	<< "\x1b[32m" \
	<< CMD \
	<< ":\x1b[0m " \
	<< ACTION << std::endl


Ping::Ping(Connexion& conn, const Message& msg)
: Command(conn, msg) {}

Ping::~Ping(void) {}


bool Ping::evaluate(void) {
	HINT("ping", "evaluate");

	return false;
}


void Ping::execute(void) {
	HINT("ping", "execute");
	std::string msg = "";
	_server.send(_conn, msg);
}

Command* Ping::create(Connexion& conn, const Message& msg) {
	return new Ping(conn, msg);
}

