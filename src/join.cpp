#include "join.hpp"

Join::Join(Connexion& conn, const Message& msg)
: Command(conn, msg) {}

Join::~Join(void) {}


bool Join::evaluate(void) {
	(void)_conn;
	(void)_msg;
	std::cout << "Join::evaluate()" << std::endl;
	return true;
}

void Join::execute(void) {
	std::cout << "Join::execute()" << std::endl;
}

Command* Join::create(Connexion& conn, const Message& msg) {
	return new Join(conn, msg);
}
