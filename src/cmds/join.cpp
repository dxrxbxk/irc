#include "join.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Join::Join(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Join::~Join(void) {}

bool Join::evaluate(void) {
	// example:
	if (not _msg.has_params())
		return false;
	return true;
}

void Join::execute(void) {
	//_server.response(_conn, "");
}

Command* Join::create(Connexion& conn, Message& msg) {
	return new Join(conn, msg);
}
