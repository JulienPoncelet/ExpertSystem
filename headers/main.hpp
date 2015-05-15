#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sys/stat.h>
# include <fstream>
# include <sstream>
# include <map>
# include <vector>
# include <complex>
# include <list>

# include <boost/config/warning_disable.hpp>
# include <boost/spirit/include/qi.hpp>
# include <boost/spirit/include/phoenix_core.hpp>
# include <boost/spirit/include/phoenix_operator.hpp>
# include <boost/spirit/include/phoenix_object.hpp>
# include <boost/fusion/include/adapt_struct.hpp>
# include <boost/fusion/include/io.hpp>
# include <boost/bind.hpp>

class System;
class Rule;

enum eFact {
	faux = 0, vrai, undefined, unsolved
};

typedef std::list<Rule> Rules;
typedef std::map<char, eFact> Facts;
typedef std::list<char> Queries;
typedef std::list<std::string> StringList;
typedef std::map<std::string, eFact> RightMap;
typedef std::list<char> CharList;

# include <Rule.hpp>
# include <System.hpp>

/* annexe.cpp */

void			uncommentLine(std::string & line);

StringList 				&split(const std::string &s, char delim, StringList &elems);
StringList 				split(const std::string &s, char delim);

/* checkInput.cpp */

char const * checkInput(int ac, char const * av[], System * sys);

#endif /* MAIN_HPP */
