#include <main.hpp>

std::string const 			System::toString(void) const {
	std::ostringstream 		out;

	out << "\033[36m";
	out << "System:" << std::endl;
	out << "\tRules:" << std::endl;

	Rules::const_iterator	rit  = getRules().begin();
	Rules::const_iterator	rite = getRules().end();

	for (; rit != rite; rit++) {
		out << "\t\tIf: " << rit->getLeft();
		out << " - Then: " << rit->getRight() << std::endl;
	}

	out << "\tFacts:" << std::endl;

	Facts::const_iterator	fit  = getFacts().begin();
	Facts::const_iterator	fite = getFacts().end();

	for (; fit != fite; fit++) {
		out << "\t\tName: " << fit->first;
		out << " - Value: " << fit->second;
		out << " (0 = false, 1 = true, 2 = undertermined)" << std::endl;
	}

	out << "\033[0m";
	return out.str();
}

System 					& System::operator=(System const & rhs) {
	setFacts(rhs.getFacts());
	setQueries(rhs.getQueries());
	return *this;
}

std::ostream 			& operator<<(std::ostream & out, System const & rhs){
	out << rhs.toString();
	return out;
}

void					System::fillSystem(char const *) {
	// std::ifstream 		in(filepath);
	// std::string 		line;

	// while (std::getline(in, line)) {
	//     std::istringstream iss(line);
	//     line = uncommentLine(line);
	//     if (line.size() == 0)
	//     	continue ;
	//     else if (line[0] == '=')
	//     	continue ;
	//     else if (line[0] == '?')
	//     	continue ;
	//     else
	//     	fillRules(line);
	// }

	return ;
}

void					System::fillRules(std::string) {
	// std::cout << line << std::endl;
	// std::regex 				avm_regex ("(!?[A-Z] ?[+^|] ?!?[A-Z])\\s*(<?=>)\\s*(!?[A-Z] ?[+^!|] ?!?[A-Z])");
	// std::smatch 			matches;
	// std::regex_match(line.cbegin(), line.cend(), matches, avm_regex);

	// std::cout << "\t" << matches[0] << std::endl;
	// std::cout << "\t" << matches[1] << std::endl;
	// std::cout << "\t" << matches[2] << std::endl;
	// std::cout << "\t" << matches[3] << std::endl;

	return ;
}
