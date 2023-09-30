#ifndef HANDLE_MESSAGE_HPP
# define HANDLE_MESSAGE_HPP

# include "types.hpp"
# include "command_factory.hpp"
# include "parser.hpp"

class Server;

void handle_message(Connexion& conn, const l_str&);


#endif
