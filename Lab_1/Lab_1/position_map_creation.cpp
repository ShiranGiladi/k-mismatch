#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "position_map_creation.h"

void createPositionMap(const std::string& filename, int wordSize, std::map<std::string, std::vector<int>>& positionMap)
{
    std::ifstream infile(filename);
    std::string text((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();

    for (int i = 0; i <= text.size() - wordSize; ++i)
    {
        std::string word = text.substr(i, wordSize);
        positionMap[word].push_back(i);
    }
}
