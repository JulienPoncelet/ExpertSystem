#include <main.hpp>

int					main(int ac, char const *av[]) {
	System 			sys;
	Rules			usedRules;

	try {
		sys.fillSystem(checkInput(--ac, ++av));
		sys.setUsedRules(usedRules);
		std::cout << sys << std::endl;
		sys.solve();
		std::cout << sys << std::endl;
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
