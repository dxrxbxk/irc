#include "join.hpp"
#include "numerics.hpp"
#include "server.hpp"

Join::Join(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Join::~Join(void) {}

Command::ret_type	Join::execute(void) {

	if (_msg.params_size() < 1) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
		return 0;
	}

	Logger::debug("JOIN: " + _conn.fullname());

	if (_server.channel_exist(_msg.params_first())) {
		Channel& channel = _server.channel(_msg.params_first());
		if (channel.invite_only() && not channel.is_invited(_conn.nickname())) {
			_conn.enqueue(RPL::invite_only_chan(_conn.info(), _msg.params_first()));
			return 0;
		}
		else if (not channel.invite_only() && channel.has_key()) {
			if (_msg.params_size() < 2 || _msg.params(1) != channel.key()) {
				_conn.enqueue(RPL::bad_channel_key(_conn.info(), _msg.params_first()));
				return 0;
			}
		}
		_conn.enter_channel(channel);
		channel.broadcast(":" + _conn.fullname() + " JOIN " + _msg.params_first() + CRLF);
		if (not channel.topic().empty())
			channel.broadcast(RPL::topic(_conn.info(), channel.name(), channel.topic()));
		// channel.add_user(_conn);
	}
	else {
		_conn.enqueue("MODE " + _msg.params_first() + " +o " + _conn.nickname() + CRLF);
		Channel& channel = _server.create_channel(_msg.params_first(), _conn);
		_conn.enter_channel(channel);
		_conn.enqueue(":" + _conn.fullname() + " JOIN " + _msg.params_first() + CRLF);
		if (not channel.topic().empty())
		    _conn.enqueue(RPL::topic(_conn.info(), channel.name(), channel.topic()));
	}
	
	return 0;

}

Command* Join::create(Connexion& conn, Message& msg) {
	return new Join(conn, msg);
}
