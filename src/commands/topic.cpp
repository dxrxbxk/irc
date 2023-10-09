#include "topic.hpp"
#include "numerics.hpp"
#include "server.hpp"
#include "channel.hpp"

Topic::Topic(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Topic::~Topic(void) {}

Command::ret_type	Topic::execute(void) {

	if (not _msg.has_params()) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), "TOPIC"));
		return 0;
	}

	const std::string& target = _msg.params(0);
	Channel& channel = Server::shared().channel(target);

	if (not _server.channel_exist(target)) {
		_conn.enqueue(RPL::no_such_channel(_conn.info(), target));
		return 0;
	}
	else if (not channel.user_in(_conn.nickname())) {
		_conn.enqueue(RPL::not_on_channel(_conn.info(), target));
		return 0;
	}
	else if (_msg.has_trailing()) {
		if (channel.topic_resrict() and not channel.is_op(_conn.nickname())) {
			_conn.enqueue(RPL::chano_privs_needed(_conn.info(), target));
			return 0;
		}
		channel.topic(_msg.trailing());
		channel.broadcast(RPL::topic(_conn.info(), target, channel.topic()));
		return 0;
	}
	else if (not _msg.has_trailing()) {
		if (channel.topic().empty()) {
			_conn.enqueue(RPL::no_topic(_conn.info(), target));
			return 0;
		}
		_conn.enqueue(RPL::topic(_conn.info(), target, channel.topic()));
		return 0;
	}
	return 0;
}

Command* Topic::create(Connexion& conn, Message& msg) {
	return new Mode(conn, msg);
}
