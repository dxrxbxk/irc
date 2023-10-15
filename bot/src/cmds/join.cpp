#include "join.hpp"
#include "bot.hpp"

Join::Join(Bot& conn, Message& msg)
: Command(conn, msg) {}

Join::~Join() {}

Command::ret_type Join::execute(void) {
	if (_msg.trailing().size() < 2)
		return 1;

	std::string& channel = _msg.trailing()[1];

	if (_msg.trailing()[1].empty() || channel[0] != '#' || channel.size() < 2)
		return 1;

	_conn.enqueue("JOIN " + channel + CRLF);
	return 0;
}

Command* Join::create(Bot& conn, Message& msg) {
	return new Join(conn, msg);
}

