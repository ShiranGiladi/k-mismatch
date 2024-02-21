#ifndef POSITION_MAP_CREATION_H
#define POSITION_MAP_CREATION_H

#include <string>
#include <vector>
#include <map>

void createPositionMap(const std::string& filename, int wordSize, std::map<std::string, std::vector<int>>& positionMap);

#endif // POSITION_MAP_CREATION_H
