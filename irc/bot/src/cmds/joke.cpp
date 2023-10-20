#include "joke.hpp"
#include "bot.hpp"

Joke::Joke(Bot& conn, Message& msg)
: Command(conn, msg) {}

Joke::~Joke() {}

Command::ret_type Joke::execute(void) {
	// randoms real jokes
	std::string rand_answer[5] = {
		"Knock knock. Who's there? A broken pencil. A broken pencil who? Nevermind, it's pointless.",
		"Knock knock. Who's there? Cows go. Cows go who? No, cows go moo!",
		"Knock knock. Who's there? Little old lady. Little old lady who? I didn't know you could yodel!",
		"Knock knock. Who's there? Tank. Tank who? You're welcome!",
		"Knock knock. Who's there? Amish. Amish who? Really? You don't look like a shoe!"
	};
	if (_msg.params_first()[0] == '#') {
		_conn.enqueue(chan_reply(rand_answer[myrand() % 5]));
	}
	return 0;
}

Command* Joke::create(Bot& conn, Message& msg) {
	return new Joke(conn, msg);
}

