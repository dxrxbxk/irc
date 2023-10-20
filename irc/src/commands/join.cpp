#include "join.hpp"
#include "numerics.hpp"
#include "server.hpp"

Join::Join(Connexion& conn, Message& msg)
: Command(conn, msg) {}

Join::~Join(void) {}

void	Join::split_channel(std::string const& channel) {

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;

	while ((pos = channel.find(',', prev)) != std::string::npos) {
		if (channel[prev] == '#' || channel[prev] == '&')
			_channels.push_back(channel.substr(prev, pos - prev));
		prev = pos + 1;
	}
	if (channel[prev] == '#' || channel[prev] == '&')
		_channels.push_back(channel.substr(prev, pos - prev));
}

void	Join::split_keys(std::string const& keys) {

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;

	while ((pos = keys.find(',', prev)) != std::string::npos) {
		_keys.push_back(keys.substr(prev, pos - prev));
		prev = pos + 1;
	}
	_keys.push_back(keys.substr(prev, pos - prev));
}

Command::ret_type	Join::execute(void) {

	if (_msg.params_size() < 1) {
		_conn.enqueue(RPL::need_more_params(_conn.info(), _msg.command()));
		return 0;
	}

	split_channel(_msg.params_first());

	if (_msg.params_size() > 1)
		split_keys(_msg.params(1));

	for (std::size_t i = 0; i < _channels.size(); ++i) {

		if (_server.channel_exist(_channels[i])) {

			Channel& channel = _server.channel(_channels[i]);

			if (channel.invite_only() && not channel.is_invited(_conn.nickname())) {
				_conn.enqueue(RPL::invite_only_chan(_conn.info(), _channels[i]));
				return 0;
			}
			else if (/*not channel.invite_only() &&*/ channel.has_key()) {
				if (i >= _keys.size() || _keys[i] != channel.key()) {
					_conn.enqueue(RPL::bad_channel_key(_conn.info(), _channels[i]));
					return 0;
				}
			}
			else if (channel.full()) {
				_conn.enqueue(RPL::channel_is_full(_conn.info(), _channels[i]));
				return 0;
			}
			else if (channel.user_in(_conn.nickname())) {
				_conn.enqueue(RPL::user_on_channel(_conn.info(), _conn.nickname(), _channels[i]));
				return 0;
			}
			_conn.enter_channel(channel);
			channel.broadcast(":" + _conn.fullname() + " JOIN " + _channels[i] + CRLF);

			if (not channel.topic().empty())
				channel.broadcast(RPL::topic(_conn.info(), channel.name(), channel.topic()));
		}

		else {

			Channel& channel = _server.create_channel(_channels[i], _conn);

			_conn.enqueue("MODE " + _channels[i] + " +o " + _conn.nickname() + CRLF);
			_conn.enter_channel(channel);
			_conn.enqueue(":" + _conn.fullname() + " JOIN " + _channels[i] + CRLF);

			if (not channel.topic().empty())
				_conn.enqueue(RPL::topic(_conn.info(), channel.name(), channel.topic()));
		}
	}
	
	return 0;

}

Command* Join::create(Connexion& conn, Message& msg) {
	return new Join(conn, msg);
}
