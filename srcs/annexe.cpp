#include <main.hpp>

void			uncommentLine(std::string & line) {
	if (line.find("#") != std::string::npos)
	{
		line.erase(line.find("#"));
	}
	while (line.find(" ") != std::string::npos){
		line.erase(line.find(" "), 1);
	}
	while (line.find("	") != std::string::npos){
		line.erase(line.find("	"), 1);
	}
}
