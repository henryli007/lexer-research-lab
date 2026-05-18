#pragma once
#include "diagengine/FixHint.h"
#include <string>
#include <vector>
namespace diagengine { struct DiagnosticExplanation { std::string code; int line; int column; std::string lexeme; std::string message; std::string explanation; std::vector<FixHint> fixes; }; }
