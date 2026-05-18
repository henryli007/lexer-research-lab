#pragma once
#include "derivative/RegexAst.h"
#include <string>
#include <vector>
namespace derivative {
struct Token { int line; int column; std::string type; std::string lexeme; };
struct Stats { size_t inputBytes; size_t tokens; size_t derivativeSteps; size_t uniqueRegexStates; size_t unsupportedChars; size_t diagnostics; double elapsedMs; };
class DerivativeLexer {
public:
    std::vector<Token> tokenize(const std::string& source, Stats* stats = 0) const;
};
}
