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
		out << " (0 = false, 1 = true, 2 = undefined, 3 = unsolved)" << std::endl;
	}

	out << "\033[0m";
	return out.str();
}

System 					& System::operator=(System const & rhs) {
	_customRule = rhs.getCustomRule();
	setRules(rhs.getRules());
	setFacts(rhs.getFacts());
	setQueries(rhs.getQueries());
	return *this;
}

std::ostream 			& operator<<(std::ostream & out, System const & rhs){
	out << rhs.toString();
	return out;
}

void					System::updateState(char fact, eFact newState) {
	Facts 				facts = getFacts();
	eFact				oldState = facts[fact];

	switch (oldState) {
		case faux :
			switch (newState) {
				case vrai :
					throw UpdateStateError(fact, oldState, newState);
					break ;
				default :
					break ;
			}
			break ;
		case vrai :
			switch (newState) {
				case faux :
					throw UpdateStateError(fact, oldState, newState);
					break ;
				default :
					break ;
			}
			break ;
		case undefined :
			switch (newState) {
				case unsolved :
					break ;
				default :
					facts[fact] = newState;
					break ;
			}
			break ;
		case unsolved :
			facts[fact] = newState;
			break ;
	}

	setFacts(facts);

	return ;
}

bool					System::isFact(char fact) {
	Facts::const_iterator	fit  = getFacts().begin();
	Facts::const_iterator	fite = getFacts().end();

	for (; fit != fite; fit++) {
		if (fact == fit->first)
			return true;
	}

	return false ;
}

eFact					System::getState(char fact) {
	Facts::const_iterator	fit  = getFacts().begin();
	Facts::const_iterator	fite = getFacts().end();

	for (; fit != fite; fit++) {
		if (fact == fit->first)
			return fit->second;
	}

	return unsolved;
}

void					System::addUsedRules(Rule const & rule) {
	Rules 				usedRules = getUsedRules();
	usedRules.push_back(rule);
	setUsedRules(usedRules);
	return ;
}

bool					System::ruleUsed(Rule const & rule) {
	Rules::const_iterator	rit  = getUsedRules().begin();
	Rules::const_iterator	rite = getUsedRules().end();

	for (; rit != rite; rit++) {
		if (rule == *rit)
			return true;
	}

	return false;
}

void					System::clearUsedRules(void) {
	Rules 				usedRules = getUsedRules();
	usedRules.clear();
	setUsedRules(usedRules);
	return ;
}

BOOST_FUSION_ADAPT_STRUCT(
	rules::rule,
	(std::string, left)
	(char, rev)
	(std::string, right)
);

BOOST_FUSION_ADAPT_STRUCT(
	rules::parent,
	(std::string, content)
);

namespace rules
{
	template <typename Iterator>
	struct rules_parser : qi::grammar<Iterator, rule(), ascii::space_type>
	{
		rules_parser() : rules_parser::base_type(start)
		{
			using qi::lexeme;
			using ascii::char_;
			using boost::optional;

			quoted_string %= lexeme[+(char_ - char_("=<"))];

			start %= quoted_string 
				>> -(char_('<')) >> "=>"
				>>  quoted_string
				;
		}
		qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
		qi::rule<Iterator, rule(), ascii::space_type> start;
	};

	template <typename Iterator>
	struct parents_parser : qi::grammar<Iterator, parent(), ascii::space_type>
	{
		parents_parser() : parents_parser::base_type(start)
		{
			using qi::lexeme;
			using qi::lit;
			using ascii::char_;
			using boost::optional;

			quoted_string %= lexeme[+(char_ - char_(")("))];

			start %= lit('(')
				>> quoted_string
				>> ')'
				>> *(char_)
				;
		}
		qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
		qi::rule<Iterator, parent(), ascii::space_type> start;
	};
}

void 					System::addFact(char const & c) {
	if (not _facts[c] and _facts[c] != unsolved)
		_facts[c] = unsolved;
}

void					System::fillSystem(char const *filepath) {
	std::ifstream 		in(filepath);
	std::string 		line;

	using boost::spirit::ascii::space;
	typedef std::string::const_iterator iterator_type;
	typedef rules::rules_parser<iterator_type> rules_parser;
	using boost::spirit::qi::parse;
	using boost::spirit::qi::upper;

	rules_parser g;
	while (std::getline(in, line)) {
		uncommentLine(line);
		if (not line.empty()){
			std::string::const_iterator iter = line.begin();
			std::string::const_iterator end = line.end();
			bool t = parse(iter, end, upper[boost::bind(&System::addFact, this, _1)]);
			while(iter != end) {
				iter++;
				t = parse(iter, end, upper[boost::bind(&System::addFact, this, _1)]);
			}
			rules::rule emp;
			emp.rev = 0;
			iter = line.begin();
			bool r = phrase_parse(iter, end, g, space, emp);

			if (r && iter == end)
				fillRules(emp);
			else {
				if (line[0] == '=') {
					for (size_t i = 1; i < line.size(); ++i)
						_facts[line[i]] = vrai;
				} else if (line[0] == '?') {
					for (size_t i = 1; i < line.size(); ++i)
						_queries.push_back(line[i]);
				}
			}
		}
	}
	return ;
}

template <typename T>
void					display(T s) {
	std::cout << boost::fusion::tuple_open('[');
	std::cout << boost::fusion::tuple_close(']');
	std::cout << boost::fusion::tuple_delimiter(",");

	std::cout << boost::fusion::as_vector(s) << std::endl;
}

void					System::parent(std::string & rule) {
	using boost::spirit::ascii::space;
	typedef std::string::const_iterator iterator_type;
	typedef rules::parents_parser<iterator_type> parents_parser;

	parents_parser p;
	rules::parent s;
	std::string::const_iterator iter = rule.begin();
	std::string::const_iterator end = rule.end();
	bool r = phrase_parse(iter, end, p, space, s);
	if (r && iter == end) {
		// std::cout << "in parent: ";
		// display(s);
		_rules.push_back(Rule(s.content, std::string(1, _customRule)));
		rule.replace(rule.find(s.content) - 1, s.content.size() + 2, std::string(1, _customRule));
		addFact(_customRule);
		incrementCustomRule();
	}
}

void					System::fillRules(rules::rule & emp) {
	// display(emp);
	if (emp.left.find("(") != std::string::npos)
		parent(emp.left);
	if (emp.right.find("(") != std::string::npos)
		parent(emp.right);
	_rules.push_back(Rule(emp.left, emp.right));
	if (emp.rev)
		_rules.push_back(Rule(emp.right, emp.left));
	return ;
}

void					System::printSoluce(void) const {
	Facts 				facts = getFacts();
	Queries::const_iterator	qit  = getQueries().begin();
	Queries::const_iterator	qite = getQueries().end();

	if (getVerbose())
		std::cout << *this << std::endl;
	else {
		std::cout << "\033[36m";
		for (; qit != qite; qit++) {
			std::cout << "Fact: " << *qit;
			std::cout << " - Value: " << facts[*qit];
			std::cout << " (0 = false, 1 = true, 2 = undefined, 3 = unsolved)" << std::endl;
		}
		std::cout << "\033[0m";
	}

	return ;
}
