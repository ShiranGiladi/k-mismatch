#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "combinations.h"

std::string readRandomText(const std::string& filename)
{
    std::ifstream infile(filename);
    std::stringstream buffer;
    buffer << infile.rdbuf();
    return buffer.str();
}

std::vector<std::string> createMap(Forms mcs) {
	//Read the random text
    std::string txt = readRandomText("random_text.txt");
    std::map<Forms, int> resMap;



}