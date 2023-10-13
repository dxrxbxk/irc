#include "hello.hpp"
#include "bot.hpp"

Hello::Hello(Bot& conn, Message& msg)
: Command(conn, msg) {}

Hello::~Hello() {}

Command::ret_type Hello::execute(void) {

//	PRINT("yoooo");
	_conn.enqueue(gen_reply(":hello"));

	return 0;
}

Command* Hello::create(Bot& conn, Message& msg) {
	return new Hello(conn, msg);
}

