#include "join.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Join::Join(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Join::~Join(void) {}

void	Join::add_user_to_channel(void) {
	Channel	&chan = _server.get_channel(_msg.get_middle(0), _conn);
//	std::string nickname = _conn.get_nickname();
//	srv.add_channel(_msg.middle
}

SendInfo Join::execute(void) {
	SendInfo	send_info;
	//check_params etc;
	//_server.response(_conn, "");
	add_user_to_channel();
	return send_info;
}

Command* Join::create(Connexion& conn, Message& msg) {
	return new Join(conn, msg);
}
