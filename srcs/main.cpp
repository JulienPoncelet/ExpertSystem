#include <main.hpp>

int					main(int ac, char const *av[]) {
	System 			sys;

	try {
		sys.fillSystem(checkInput(--ac, ++av));
		std::cout << sys << std::endl;
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
