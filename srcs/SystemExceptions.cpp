#include <main.hpp>

System::UpdateStateError::UpdateStateError(char fact2, eFact from2, eFact to2) {
	fact = fact2;
	from = from2;
	to = to2;
}
System::UpdateStateError	& System::UpdateStateError::operator=(System::UpdateStateError const & rhs) {
	fact = rhs.fact;
	from = rhs.from;
	to = rhs.to;
	return *this;
}
const char 					* System::UpdateStateError::what(void) const throw() {
	char					* buffer = new char [1024];
	char					* fromString = new char [1024];
	char					* toString = new char [1024];

	switch (from) {
		case faux :
			strcpy(fromString, "false");
			break ;
		case vrai :
			strcpy(fromString, "true");
			break ;
		case undefined :
			strcpy(fromString, "undefined");
			break ;
		case unsolved : 
			strcpy(fromString, "unsolved");
			break ;
	}

	switch (to) {
		case faux :
			strcpy(toString, "false");
			break ;
		case vrai :
			strcpy(toString, "true");
			break ;
		case undefined :
			strcpy(toString, "undefined");
			break ;
		case unsolved : 
			strcpy(toString, "unsolved");
			break ;
	}

	strcpy(buffer, "\033[31m");
	strcat(buffer, "Error while trying to change the fact '");
	strcat(buffer, &fact);
	strcat(buffer, "'\n");
	strcat(buffer, "A state can't pass from `");
	strcat(buffer, fromString);
	strcat(buffer, "` to `");
	strcat(buffer, toString);
	strcat(buffer, "`\033[0m\n");


	return buffer;
}