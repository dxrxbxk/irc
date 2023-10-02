#include "command.hpp"
#include "server.hpp"

Command::Command(Connexion& conn, Message& msg)
: _msg(msg), _conn(conn), _server(conn.getServer()) {
	(void)_msg;
	(void)_conn;
}

Command::~Command(void) {}
