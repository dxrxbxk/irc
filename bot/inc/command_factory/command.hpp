#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "message.hpp"

// forward declaration
class Bot;

enum {
	DO_NOTHING,
	SEND
};

#define CRLF "\r\n"

class Command {

	public:
		typedef int ret_type;

		Command(Bot&, Message&);

		virtual ~Command(void);

		virtual ret_type execute() = 0;


	protected:

		Message& _msg;
		Bot&	_conn;
		const std::string	gen_reply(const std::string& text);
};

#endif
