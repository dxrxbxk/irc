#ifndef JOIN_HPP
# define JOIN_HPP

#include "command.hpp"


class Join : public Command {

	public:

		Join(Connexion& conn, const Message& msg) : Command(conn, msg) {}
		~Join(void);

		bool evaluate() {
			std::cout << "Join::evaluate()" << std::endl;
		}

		void execute() {
			std::cout << "Join::execute()" << std::endl;
		}

		static Command* create(const Message& msg) {
			return new Join(msg);
		}

	private:

};

#endif
