#pragma once

#include <string>

#include "cminus/common/LexResult.h"

namespace cminus {

class Lexer {
public:
    LexResult tokenize(const std::string& source);
};

} // namespace cminus
