
#include "quit.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Quit::Quit(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Quit::~Quit(void) {}

Command::ret_type	Quit::execute(void) {
//	_server.remove_newcomer(_conn);
	return -1;
}

Command* Quit::create(Connexion& conn, Message& msg) {
	return new Quit(conn, msg);
}
