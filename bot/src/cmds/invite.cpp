#include "invite.hpp"
#include "bot.hpp"

Invite::Invite(Bot& conn, Message& msg)
: Command(conn, msg) {}

Invite::~Invite() {}

Command::ret_type Invite::execute(void) {
	if (_msg.params_first().size() < 3)
		return 1;

	std::string& channel = _msg.params()[2];
	std::string& nick = _msg.params()[0];

	if (channel.empty() || channel[0] != '#' || channel.size() < 2)
		return 1;

	_conn.enqueue("JOIN " + channel + CRLF);
	_conn.enqueue("PRIVMSG " + channel + " :Thanks for the invite @" + nick + "!" + CRLF);
	return 0;
}

Command* Invite::create(Bot& conn, Message& msg) {
	return new Invite(conn, msg);
}

