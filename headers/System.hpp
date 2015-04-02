#ifndef System_HPP
# define System_HPP

class System {

private:

	Rules				_rules;
	Facts				_facts;
	Queries				_queries;

public:

	System(void) {}
	System(System const & src) { *this = src; }
	virtual ~System(void) {}

	std::string 		const toString(void) const;
	System				& operator=(System const & rhs);

	void				fillSystem(char const *filepath);
	void				fillRules(std::string line);
	void				resolve(void);
	void				respond(void) const;

	Rules const & 		getRules(void) const { return _rules; }
	Facts const & 		getFacts(void) const { return _facts; }
	Queries const &		getQueries(void) const { return _queries; }

	void				setRules(Rules const & rules) { _rules = rules; }
	void				setFacts(Facts const & facts) { _facts = facts; }
	void				setQueries(Queries const & queries) { _queries = queries; }

};

std::ostream 			& operator<<(std::ostream & out, System const & rhs);

#endif /* System_HPP */
