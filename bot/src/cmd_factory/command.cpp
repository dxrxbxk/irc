#include "command.hpp"
#include "bot.hpp"

const std::string	Command::gen_reply(const std::string& text) {
	std::string reply(":");
	reply.append(_conn.fullname());
	reply.append(" ");
	reply.append(_msg.command());
	reply.append(" ");
	reply.append(_msg.params_first());
	reply.append(" ");
	reply.append(text);
	reply.append(CRLF);
	return reply;
}

Command::Command(Bot& conn, Message& msg)
: _msg(msg), _conn(conn) {
	(void)_msg;
	(void)_conn;
}

Command::~Command(void) {}
