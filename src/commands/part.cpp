#include "part.hpp"
#include "server.hpp"

Part::Part(Connexion& c, Message& m) : Command(c, m) {}

Part::~Part(void) {}

Command::ret_type	Part::execute(void)
{
	if (not _msg.has_params()) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
		return 0;
	}

	const std::string& param = _msg.params(0);
	if (not _server.channel_exist(param)) {
		_conn.enqueue(RPL::no_such_channel(_conn.info(), param));
		return 0;
	}
	Channel& channel = _server.channel(param);
	if (not channel.user_in(_conn.nickname())) {
		_conn.enqueue(RPL::not_on_channel(_conn.info(), param));
		return 0;
	}

//	channel.broadcast(":" + _conn.nickname() + " PART " + param + CRLF, _conn);
	channel.broadcast(gen_reply(param));
//	_conn.enqueue(":" + _conn.nickname() + " PART " + param + CRLF);
	channel.rm_user_and_channel(_conn);
	return 0;
}

Command* Part::create(Connexion& conn, Message& msg) {
	return new Part(conn, msg);
}
