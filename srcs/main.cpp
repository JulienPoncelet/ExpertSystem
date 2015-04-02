#include <main.hpp>

int					main(int ac, char const *av[]) {
	System 			sys;
	Rules			rules;
	Facts			facts;
	Queries			queries;

	rules.push_back(Rule("C", "E"));
	rules.push_back(Rule("A + B + C", "D"));
	rules.push_back(Rule("A | B", "C"));
	rules.push_back(Rule("A + !B", "F"));
	rules.push_back(Rule("C | !G", "H"));
	rules.push_back(Rule("V ^ W", "Y"));
	rules.push_back(Rule("A + B", "Y + Z"));
	rules.push_back(Rule("C | D", "X | V"));
	rules.push_back(Rule("E + F", "!V"));
	rules.push_back(Rule("A + B", "C"));
	rules.push_back(Rule("C", "A + B"));

	facts.push_back(Fact('A', vrai));
	facts.push_back(Fact('B', vrai));
	facts.push_back(Fact('G', vrai));
	facts.push_back(Fact('C', unsolved));
	facts.push_back(Fact('D', unsolved));
	facts.push_back(Fact('E', unsolved));
	facts.push_back(Fact('F', unsolved));
	facts.push_back(Fact('H', unsolved));
	facts.push_back(Fact('V', unsolved));
	facts.push_back(Fact('W', unsolved));
	facts.push_back(Fact('X', unsolved));
	facts.push_back(Fact('Y', unsolved));
	facts.push_back(Fact('Z', unsolved));

	queries.push_back('G');
	queries.push_back('V');
	queries.push_back('X');

	try {
		sys.fillSystem(checkInput(--ac, ++av));
		sys.setRules(rules);
		sys.setFacts(facts);
		sys.setQueries(queries);
		std::cout << sys << std::endl;
	}
	catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
