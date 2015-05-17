#include <main.hpp>

void				checkFile(char const * filepath) {
	struct stat buf;
	if (stat(filepath, &buf) != 0) {
		std::cerr << "\033[31mFile `" << filepath;
		std::cerr << "` doesn't exist\033[0m" << std::endl;
		exit(EXIT_FAILURE);
	}
}

char const			* checkInput(int ac, char const *av[], System * sys) {
	std::string		usage = "Usage: ./system [-v] <file>";

	switch (ac) {
	case 1:
		checkFile(av[0]);
		return av[0];
	case 2:
		if (av[0][0] != '-' or av[0][1] != 'v') {
			std::cerr << usage << std::endl;
			exit(EXIT_FAILURE);
		}
		sys->setVerbose(true);
		checkFile(av[1]);
		return av[1];
	default:
		std::cerr << usage << std::endl;
		exit(EXIT_FAILURE);
	}
}
