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

SendInfo Ping::execute(void) {
	SendInfo	send_info;
//	if (_msg.get_middle_size() < 1)
//		;
	_server.response(_conn, "PONG :" + _msg.get_middle(0));
	return send_info;
}

Command* Ping::create(Connexion& conn, Message& msg) {
	return new Ping(conn, msg);
}

