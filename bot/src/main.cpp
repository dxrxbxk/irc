#include "bot.hpp"

int	main(int ac, char **av) {
	if (ac != 3) {
		std::cerr << "Usage: ./bot <server> <password>" << std::endl;
		return 1;
	}
	Bot bot(*av + 1, *av + 2, *av + 3);
	bot.run();
	return 0;
}
