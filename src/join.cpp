#include "join.hpp"
#include "server.hpp"


#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;


Join::Join(Connexion& conn, const Message& msg)
: Command(conn, msg) {}

Join::~Join(void) {}


bool Join::evaluate(void) {
	HINT("join: evaluate");

	// example:
	if (_server.has_password()) {}

	return false;
}


void Join::execute(void) {
	HINT("join: execute");

}

Command* Join::create(Connexion& conn, const Message& msg) {
	return new Join(conn, msg);
}
