#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "message.hpp"
# include "logger.hpp"
# include "send_info.hpp"

// forward declaration
class Server;
class Connexion;

class Command {

	public:

		Command(Connexion&, Message&);

		virtual ~Command(void);

		virtual SendInfo execute() = 0;

	protected:

		Message& _msg;
		Connexion& _conn;
		Server& _server;
};

#endif
