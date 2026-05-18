#pragma once
#include "derivative/RegexAst.h"
namespace derivative {
bool nullable(const RegexPtr& r);
RegexPtr derivativeOf(const RegexPtr& r, char ch);
size_t matchPrefix(const RegexPtr& r, const std::string& input, size_t start, size_t* steps = 0, std::set<std::string>* states = 0);
}
