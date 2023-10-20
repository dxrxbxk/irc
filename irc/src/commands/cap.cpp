#include "cap.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Cap::Cap(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Cap::~Cap(void) {}

Command::ret_type Cap::execute(void) {

	if (not _msg.has_params())
		return -1;


	if (_msg.params(0) == "END")
		return 0;

	else if (_msg.params(0) == "LS") {
		_conn.enqueue("CAP * LS :" CRLF);
	}
	
	return 0;
}


Command* Cap::create(Connexion& conn, Message& msg) {
	return new Cap(conn, msg);
}
