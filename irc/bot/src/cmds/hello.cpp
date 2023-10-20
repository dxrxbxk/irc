#include "hello.hpp"
#include "bot.hpp"

Hello::Hello(Bot& conn, Message& msg)
: Command(conn, msg) {}

Hello::~Hello() {}

Command::ret_type Hello::execute(void) {
	std::string rand_answer[5] = {
		"Hello :D",
		"Hi :D",
		"Hey :D",
		"Hi there :D",
		"Hello there :D"
	};

	if (_msg.params_first()[0] == '#') {
		_conn.enqueue(chan_reply(rand_answer[myrand() % 5]));
	}
	return 0;
}

Command* Hello::create(Bot& conn, Message& msg) {
	return new Hello(conn, msg);
}

