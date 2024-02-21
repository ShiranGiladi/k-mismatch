#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "createQueries.h"

std::string readTextFromFile(const std::string& filename)
{
    std::ifstream infile(filename);
    std::stringstream buffer;
    buffer << infile.rdbuf();
    return buffer.str();
}

std::vector<std::string> generateQueries(int s, int numberOfQueries)
{
    std::string txt = readTextFromFile("random_text.txt");
    std::vector<std::string> queries;
    for (int i = 0; i < numberOfQueries; i++)
    {
        std::string query;
        for (int j = 0; j < s; j++)
        {
            query += txt[i + j];
        }
        queries.push_back(query);
    }
    return queries;
}
