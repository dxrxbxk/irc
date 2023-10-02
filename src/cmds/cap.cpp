#include "cap.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Cap::Cap(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Cap::~Cap(void) {}

bool Cap::evaluate(void) {
	return true;
}

void Cap::execute(void) {
//	_server.response(_conn, "CAP * LS :");
	if (_msg.get_middle(0) == "END")
		return ;
	else if (_msg.get_middle(0) == "LS")
		_server.response(_conn, "CAP * LS :\r\n");
}

Command* Cap::create(Connexion& conn, Message& msg) {
	return new Cap(conn, msg);
}
