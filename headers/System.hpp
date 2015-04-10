#ifndef System_HPP
# define System_HPP

namespace rules
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;

	struct rule
	{
		std::string left;
		char rev;
		std::string right;
	};
	
	struct parent
	{
		std::string content;
	};
}

class System {

private:

	Rules				_rules;
	Facts				_facts;
	Queries				_queries;
	char				_customRule;
	Rules				_usedRules;

public:

	class UpdateStateError : public std::exception {

	public:

		UpdateStateError(void) {}
		UpdateStateError(char fact, eFact from, eFact to);

		UpdateStateError(UpdateStateError const & src) { *this = src; }
		UpdateStateError		& operator=(UpdateStateError const & rhs);
		virtual const char 		* what(void) const throw();

		char					fact;
		eFact					from;
		eFact					to;

	};

	System(void) : _customRule('a') {}
	System(System const & src) { *this = src; }
	virtual ~System(void) {}

	std::string 		const toString(void) const;
	System				& operator=(System const & rhs);

	// System.cpp

	void				updateState(char fact, eFact newState);
	bool				isFact(char fact);
	eFact				getState(char fact);
	bool				ruleUsed(Rule const & rule);
	void				clearUsedRules(void);
	void				fillSystem(char const *filepath);
	void				fillRules(rules::rule & emp);
	void				parent(std::string & rule);
	void				resolve(void);
	// void				respond(void) const;

	Rules const & 		getRules(void) const { return _rules; }
	Facts const & 		getFacts(void) const { return _facts; }
	Queries const &		getQueries(void) const { return _queries; }
	char 				getCustomRule(void) const { return _customRule; }
	Rules const & 		getUsedRules(void) const { return _usedRules; }

	void				setRules(Rules const & rules) { _rules = rules; }
	void				setFacts(Facts const & facts) { _facts = facts; }
	void				setQueries(Queries const & queries) { _queries = queries; }
	void				incrementCustomRule(void) { _customRule++; }
	void				setUsedRules(Rules const & rules) { _usedRules = rules; }
	void				addUsedRules(Rule const & rule);
	void				addFact(char const & c);

	// SystemSolver.cpp

	void				solve(void);
	void				solveFact(char fact, eFact oldState);
	eFact				solveRule(Rule rule, char fact);
	eFact				evaluateLeft(std::string lhs);
	eFact				tryRight(std::string rhs, char fact, eFact wanted);
	std::string::iterator 	subLeft(std::string::iterator it, eFact & currentState, char ope);
	std::string::iterator 	subRight(std::string::iterator it, eFact & currentState, char fact, eFact wanted, char ope);
};

std::ostream 			& operator<<(std::ostream & out, System const & rhs);

#endif /* System_HPP */
