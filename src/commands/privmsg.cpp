#include "privmsg.hpp"
#include "server.hpp"

Privmsg::Privmsg(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Privmsg::~Privmsg(void) {}


Command::ret_type	 Privmsg::execute(void) {

	// if (_msg.params_size() != 1
	// 	|| not _msg.has_trailing())
	// 	return;


	// if (_server.channel_exist(_msg.param(0))) {
		Channel& channel = _server.get_channel(_msg.params_first(), _conn);
		std::string msg(":");
		msg.append(_conn.nickname());
		msg.append("!");
		msg.append(_conn.username());
		msg.append("@");
		msg.append(_conn.hostname());
		msg.append(" PRIVMSG ");
		msg.append(_msg.params_first());
		msg.append(" ");
		msg.append(_msg.trailing());
		msg.append(CRLF);

//		Logger::debug(msg);

		channel.broadcast(msg, _conn);
	// }
	// else if (_server.user_exists(_msg.param(0))) {
	// 	User& user = _server.get_user(_msg.param(0));
	// 	user.send(_msg);
	// }
		return 0;

}

Command* Privmsg::create(Connexion& conn, Message& msg) {
	return new Privmsg(conn, msg);
}
