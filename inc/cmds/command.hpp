#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "message.hpp"
# include "logger.hpp"
# include "send_info.hpp"
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

		Command(Connexion&, Message&);

		virtual ~Command(void);

		virtual void execute() = 0;

	protected:

		Message& _msg;
		Connexion& _conn;
		Server& _server;
};

#endif
