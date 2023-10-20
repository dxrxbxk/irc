#include "part.hpp"
#include "bot.hpp"

Part::Part(Bot& conn, Message& msg)
: Command(conn, msg) {}

Part::~Part() {}

Command::ret_type Part::execute(void) {
	std::string rand_answer[5] = {
		"Bye :D",
		"Bye bye :D",
		"See you :D",
		"See you later :D",
		"Bye bye bye :D"
	};
	if (_msg.params_first()[0] == '#') {
		_conn.enqueue(chan_reply(rand_answer[myrand() % 5]));
		_conn.enqueue("PART " + _msg.params_first() + CRLF);
	}
	return 0;
}

Command* Part::create(Bot& conn, Message& msg) {
	return new Part(conn, msg);
}

