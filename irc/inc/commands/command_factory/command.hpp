#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "message.hpp"
# include "numeric_factory.hpp"

// forward declaration
class Server;
class Connexion;

enum {
	DO_NOTHING,
	SEND
};

#define CRLF "\r\n"

class Command {

	public:
		typedef int ret_type;

		Command(Connexion&, Message&);

		virtual ~Command(void);

		virtual ret_type execute() = 0;


	protected:

		Message& _msg;
		Connexion& _conn;
		Server& _server;
		const std::string	gen_reply(const std::string& text);
};

#endif
