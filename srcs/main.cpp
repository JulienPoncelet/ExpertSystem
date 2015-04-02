#include <main.hpp>

int					main(int ac, char const *av[]) {
	System 			sys;
	Rules			rules;
	Facts			facts;
	Queries			queries;
	Rules			usedRules;

	rules.push_back(Rule("C", "E"));
	rules.push_back(Rule("A+B+C", "D"));
	rules.push_back(Rule("A|B", "C"));
	rules.push_back(Rule("A+!B", "F"));
	rules.push_back(Rule("C|!G", "H"));
	rules.push_back(Rule("V^W", "Y"));
	rules.push_back(Rule("A+B", "Y+Z"));
	rules.push_back(Rule("C|D", "X|V"));
	rules.push_back(Rule("E+F", "!V"));
	rules.push_back(Rule("A+B", "C"));
	rules.push_back(Rule("C", "A+B"));
	// rules.push_back(Rule("(A + B) | H", "V"));
	rules.push_back(Rule("A+B", "a"));
	rules.push_back(Rule("a|H", "V"));

	facts['A'] = vrai;
	facts['B'] = vrai;
	facts['G'] = vrai;
	facts['C'] = unsolved;
	facts['D'] = unsolved;
	facts['E'] = unsolved;
	facts['F'] = unsolved;
	facts['H'] = unsolved;
	facts['V'] = unsolved;
	facts['W'] = unsolved;
	facts['X'] = unsolved;
	facts['Y'] = unsolved;
	facts['Z'] = unsolved;
	facts['a'] = unsolved;

	queries.push_back('G');
	queries.push_back('V');
	queries.push_back('X');

	try {
		sys.fillSystem(checkInput(--ac, ++av));
		sys.setRules(rules);
		sys.setFacts(facts);
		sys.setQueries(queries);
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
