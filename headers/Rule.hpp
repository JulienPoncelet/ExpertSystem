#ifndef RULE_CLASS
# define RULE_CLASS

class Rule {

private:

	std::string		_left;
	std::string		_right;

public:

	// constructor/destructor
	Rule(void) {}
	Rule(std::string left, std::string right) : _left(left), _right(right) {}
	Rule(Rule const & rule) { *this = rule; }
	virtual ~Rule(void) {}

	// member function
	std::string const string(void) const;

	// accessors
	std::string const & getLeft(void) const { return _left; }
	std::string const & getRight(void) const { return _right; }
	void setLeft(std::string const & left) { _left = left; }
	void setRight(std::string const & right) { _right = right; }

	Facts & resolve(Facts & facts);
	
	//operator overload
	Rule & operator=(Rule const & rule) {
		setLeft(rule.getLeft());
		setRight(rule.getRight());
		return *this;
	}
};
// stream overload
std::ostream & operator<<(std::ostream & o, Rule const & rule);

#endif