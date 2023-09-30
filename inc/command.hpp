#ifndef COMMAND_HPP
# define COMMAND_HPP

// # include "connexion.hpp"
# include "message.hpp"

// forward declaration
class Connexion;
class Server;

class Command {

	public:

		Command(Connexion&, const Message&);

		virtual ~Command(void);


		virtual bool evaluate() = 0;

		virtual void execute() = 0;

	protected:

		const Message& _msg;
		Connexion& _conn;
		Server& _server;

};

#endif
