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

void	Join::add_user_to_channel(void) {
	Server &srv = _conn.getServer();
	Channel	&chan = srv.get_channel(_msg.get_middle(0), _conn);
//	std::string nickname = _conn.get_nickname();
//	srv.add_channel(_msg.middle
}

void Join::execute(void) {
	//_server.response(_conn, "");
	add_user_to_channel();
	_server.response(_conn, RPL::welcome(_conn.get_client_info()));
}

Command* Join::create(Connexion& conn, Message& msg) {
	return new Join(conn, msg);
}
