#include "cap.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Cap::Cap(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Cap::~Cap(void) {}

void Cap::execute(void) {

	if (not _msg.has_params())
		return;


	if (_msg.param(0) == "END")
		return;

	else if (_msg.param(0) == "LS") {
		_conn.enqueue("CAP * LS :" CRLF);
	}
}


Command* Cap::create(Connexion& conn, Message& msg) {
	return new Cap(conn, msg);
}
