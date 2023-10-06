#include "join.hpp"
#include "numerics.hpp"
#include "server.hpp"

//443,475,473, 471

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Join::Join(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Join::~Join(void) {}

Command::ret_type	Join::execute(void) {

	if (_msg.params_size() != 1) {
		return -1;
	}

	if (_server.channel_exist(_msg.params_first())) {
		Channel& channel = _server.channel(_msg.params_first());
		_conn.enter_channel(channel);
		// channel.add_user(_conn);
	}
	else {
		Channel& channel = _server.create_channel(_msg.params_first(), _conn);
		_conn.enter_channel(channel);
	}
	
	return 0;

}

Command* Join::create(Connexion& conn, Message& msg) {
	return new Join(conn, msg);
}
