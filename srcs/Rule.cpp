#include <main.hpp>

std::string const Rule::string(void) const {
	std::ostringstream 		out;
	out << "Not yet";
	return out.str();
}
 
Facts & Rule::resolve(Facts & facts) {
	return facts;
}