#include "command.hpp"

Command::Command(Connexion& conn, const Message& msg)
: _msg(msg), _conn(conn) {
	(void)_msg;
	(void)_conn;
}

Command::~Command(void) {}
