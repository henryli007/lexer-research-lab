#pragma once
#include "cminus/common/LexResult.h"
#include <string>
#include <vector>
namespace proptest {
struct PropertyOutcome { std::string name; bool pass; };
std::vector<PropertyOutcome> checkProperties(const std::string& source, const cminus::LexResult& result, double elapsedMs);
}
