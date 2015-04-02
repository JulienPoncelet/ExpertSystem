#include <main.hpp>

std::string const 	Rule::toString(void) const {
	std::ostringstream 		out;
	out << "If: " << getLeft();
	out << " - Then: " << getRight() << std::endl;
	return out.str();
}
 
Facts 				Rule::solve(Facts facts) {
	std::cout << *this << std::endl;
	return facts;
}

bool				operator==(Rule const lhs, Rule const rhs) {
	if (lhs.getLeft() != rhs.getLeft())
		return false;
	if (lhs.getRight() != rhs.getRight())
		return false;
	return true ;
}

std::ostream & 		operator<<(std::ostream & out, Rule const & rhs) {
	out << rhs.toString();
	return out;
}

