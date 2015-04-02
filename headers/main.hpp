#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sys/stat.h>
# include <fstream>
# include <sstream>
# include <map>
# include <list>

class System;
class Rule;

enum eFact {
	faux = 0, vrai, undefined, unsolved
};

typedef std::list<Rule> Rules;
typedef std::map<char, eFact> Facts;
typedef std::list<char> Queries;
typedef std::list<std::string> StringList;

# include <Rule.hpp>
# include <System.hpp>

/* annexe.cpp */

std::string				uncommentLine(std::string line);

std::string 			trim(std::string s);
std::string 			ltrim(std::string s);
std::string				rtrim(std::string s);

StringList 				&split(const std::string &s, char delim, StringList &elems);
StringList 				split(const std::string &s, char delim);

/* checkInput.cpp */

char const * checkInput(int ac, char const * av[]);

#endif /* MAIN_HPP */
