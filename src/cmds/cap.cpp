#include "cap.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Cap::Cap(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Cap::~Cap(void) {}

SendInfo Cap::execute(void) {
	SendInfo	send_info;
//	_server.response(_conn, "CAP * LS :");
	if (_msg.get_middle(0) == "END")
		return send_info;
	else if (_msg.get_middle(0) == "LS")
		_server.response(_conn, "CAP * LS :\r\n");
	return send_info;
}

Command* Cap::create(Connexion& conn, Message& msg) {
	return new Cap(conn, msg);
}
