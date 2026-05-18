#pragma once
#include "cminus/common/Token.h"
#include <vector>
namespace roundtrip { class TokenPrinter { public: std::string print(const std::vector<cminus::Token>& tokens) const; }; }
