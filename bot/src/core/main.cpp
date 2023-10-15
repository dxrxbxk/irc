#include "bot.hpp"

int	main(int ac, char **av) {
	if (ac == 3) {
		try {
			Bot bot(av[1], av[2]);
			bot.run();
		} catch (const std::exception &e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}
	else {
		std::cerr << "Usage: ./bot <port> <password>" << std::endl;
		return 1;
	}
	return 0;
}
