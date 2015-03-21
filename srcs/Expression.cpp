#include <main.hpp>

std::string const 			Expression::toString(void) const {
	std::ostringstream 		out;

	out << getValue();
	return out.str();
}

Expression 					& Expression::operator=(Expression const & rhs) {
	(void)rhs;
	return *this;
}

std::ostream 				& operator<<(std::ostream & out, Expression const & rhs){
	out << rhs.toString();
	return out;
}
