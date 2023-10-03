#include "ping.hpp"
#include "server.hpp"


#define HINT(CMD, ACTION) std::cout \
	<< "\x1b[32m" \
	<< CMD \
	<< ":\x1b[0m " \
	<< ACTION << std::endl


Ping::Ping(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Ping::~Ping() {}

void Ping::execute(void) {

	if (_msg.params_size() < 1)
		return;

	_conn.enqueue("PONG :" + _msg.param(0) + CRLF);
}

Command* Ping::create(Connexion& conn, Message& msg) {
	return new Ping(conn, msg);
}

