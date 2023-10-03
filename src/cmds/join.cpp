#include "join.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Join::Join(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Join::~Join(void) {}


void	 Join::execute(void) {

	if (_msg.params_size() != 1)
		return;

	// Channel& channel = _server.get_channel(_msg.param(0), _conn);

	if (_server.channel_exist(_msg.param(0))) {
		Channel& channel = _server.channel(_msg.param(0));
		_conn.enter_channel(channel);
		// channel.add_user(_conn);
	}
	else {
		Channel& channel = _server.create_channel(_msg.param(0), _conn);
		_conn.enter_channel(channel);
	}

}

Command* Join::create(Connexion& conn, Message& msg) {
	return new Join(conn, msg);
}
