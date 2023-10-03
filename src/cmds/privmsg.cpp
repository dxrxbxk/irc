#include "privmsg.hpp"
#include "server.hpp"

#define HINT(MSG) std::cout << "\x1b[32m" << MSG << "\x1b[0m" << std::endl;

Privmsg::Privmsg(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Privmsg::~Privmsg(void) {}


void	 Privmsg::execute(void) {

	// if (_msg.params_size() != 1
	// 	|| not _msg.has_trailing())
	// 	return;


	// if (_server.channel_exist(_msg.param(0))) {
		Channel& channel = _server.get_channel(_msg.param(0), _conn);
		std::string msg(":");
		msg.append(_conn.nickname());
		msg.append("!");
		msg.append(_conn.username());
		msg.append("@");
		msg.append(_conn.hostname());
		msg.append(" PRIVMSG ");
		msg.append(_msg.param(0));
		msg.append(" :");
		msg.append(_msg.trailing());
		msg.append(CRLF);

		channel.broadcast(msg, _conn);
	// }
	// else if (_server.user_exists(_msg.param(0))) {
	// 	User& user = _server.get_user(_msg.param(0));
	// 	user.send(_msg);
	// }

}

Command* Privmsg::create(Connexion& conn, Message& msg) {
	return new Privmsg(conn, msg);
}
