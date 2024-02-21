#ifndef CREATEQUERIES_H
#define CREATEQUERIES_H

#include <string>
#include <vector>

std::string readTextFromFile(const std::string& filename);

std::vector<std::string> generateQueries(int s, int numberOfQueries);

#endif // CREATEQUERIES_H
