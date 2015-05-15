#include <main.hpp>

int					main(int ac, char const *av[]) {
	System 			* sys = new System;
	Rules			usedRules;

	try {
		sys->fillSystem(checkInput(--ac, ++av, sys));
		sys->setUsedRules(usedRules);
		sys->solve();
		sys->printSoluce();
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
