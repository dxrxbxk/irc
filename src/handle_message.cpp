#include "handle_message.hpp"



void handle_message(Connexion& conn, const l_str& msgs) {

	for (l_str::const_iterator i = msgs.begin(); i != msgs.end(); ++i) {

		try {
			// parse raw message
			Message msg = Parser::parse(*i);
			msg.print();

			Command* cmd = CommandFactory::create(conn, msg);

			if (cmd == NULL)
				std::cout << "Command not found" << std::endl;
			else {
				if (cmd->evaluate() == true)
					cmd->execute();
				delete cmd;
			}

		} catch (const std::exception& e) {
			std::cerr << "Parsing error" << e.what() << std::endl;
		}
	}
}
