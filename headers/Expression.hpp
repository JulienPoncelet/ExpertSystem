#ifndef Expression_HPP
# define Expression_HPP

class Expression {

private:

	std::string 		_value;
	Facts				_facts;

public:

	Expression(void) {} // Don't use this
	Expression(std::string value) { setValue(value); }
	Expression(Expression const & src) { *this = src; }
	virtual ~Expression(void) {}

	std::string 		const toString(void) const;
	Expression			& operator=(Expression const & rhs);

	std::string 		getValue(void) const { return _value; }
	Facts 		 		getFacts(void) const { return _facts; }

	void				setValue(std::string const & value) { _value = value; }
	void				setFacts(Facts const & facts) { _facts = facts; }

};

std::ostream 			& operator<<(std::ostream & out, Expression const & rhs);

#endif /* Expression_HPP */
