#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "connexion.hpp"
# include "message.hpp"


class Command {

	public:

		Command(Connexion& conn, const Message& msg) : _msg(msg), _conn(conn) {}
		~Command(void);


		virtual void evaluate() = 0;
		virtual void execute() = 0;

	private:

		const Message& _msg;
		Connexion& _conn;

};










#endif
