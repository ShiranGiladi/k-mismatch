#ifndef _INC_MCS
#define _INC_MCS

#include "combinations.h"

std::vector<Forms> buildMCS(int length, int mismatchK, int matchesPerForm);

bool CheckQueryOnPosition(const std::string& query, int64_t position, size_t maxMismatchs);

#endif // _INC_MCS
