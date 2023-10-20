#include "command.hpp"
#include "kick.hpp"
#include "server.hpp"

Kick::Kick(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Kick::~Kick(void) {}

Command::ret_type	Kick::execute(void) {
	
	if (_msg.params_size() < 2) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
		return 0;
	}

	const std::string& channel_name = _msg.params(0);
	const std::string& nickname = _msg.params(1);

	if (not _server.nick_exist(nickname)) {
		_conn.enqueue(RPL::no_such_nick(_conn.info(), nickname));
		return 0;
	}
	else if (not _server.channel_exist(channel_name)) {
		_conn.enqueue(RPL::no_such_channel(_conn.info(), channel_name));
		return 0;
	}

	Channel& channel = _server.get_channel(channel_name);

	if (not channel.user_in(nickname)) {
		_conn.enqueue(RPL::not_on_channel(_conn.info(), channel_name));
		return 0;
	}
	else if (not channel.is_op(_conn.nickname())) {
		_conn.enqueue(RPL::chano_privs_needed(_conn.info(), channel_name));
		return 0;
	}
	Connexion& user = _server.get_conn(nickname);
	channel.broadcast(":" + _conn.nickname() + " KICK "
			+ channel_name + " " + nickname + " " + ":yeeeet" + CRLF);
	channel.rm_user_and_channel(user);

	return 0;
}

Command* Kick::create(Connexion& conn, Message& msg) {
	return new Kick(conn, msg);
}
