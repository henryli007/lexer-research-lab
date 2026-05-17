#pragma once

#include <string>
#include <vector>

#include "cminus/common/Diagnostic.h"
#include "cminus/common/Token.h"

namespace cminus {

struct LexResult {
    bool success = false;
    std::vector<Token> tokens;
    std::string errorMessage;
    std::vector<Diagnostic> diagnostics;
};

} // namespace cminus
