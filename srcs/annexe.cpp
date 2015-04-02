#include <main.hpp>

std::string				uncommentLine(std::string line) {
	line = line.substr(0, line.find('#'));
	line = line.substr(0, line.find('\n'));
	return trim(line);
}

std::string 			trim(std::string s) {
        return ltrim(rtrim(s));
}

std::string 			ltrim(std::string s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

std::string				rtrim(std::string s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

StringList 				&split(const std::string &s, char delim, StringList &elems) {
    std::stringstream 	ss(s);
    std::string 		item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

StringList 				split(const std::string &s, char delim) {
    StringList 			elems;
    split(s, delim, elems);
    return elems;
}
