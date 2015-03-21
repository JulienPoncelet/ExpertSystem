#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <sys/stat.h>
# include <fstream>
# include <sstream>
# include <map>
# include <list>
# include <regex>

class System;
class Expression;

typedef std::map<char, bool> Facts;
typedef std::list<char> Queries;

# include <Expression.hpp>

typedef std::map<Expression, Expression> Rules;

# include <System.hpp>

/* annexe.cpp */

std::string				uncommentLine(std::string line);

std::string 			trim(std::string s);
std::string 			ltrim(std::string s);
std::string				rtrim(std::string s);

/* checkInput.cpp */

char const * checkInput(int ac, char const * av[]);

#endif /* MAIN_HPP */
