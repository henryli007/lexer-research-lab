#pragma once
#include "modes/ModeToken.h"
#include <string>
#include <vector>
namespace modes { struct ModeStats { size_t tokens; size_t transitions; long long elapsedUs; }; class ModeLexer { public: std::vector<ModeToken> tokenizeCminus(const std::string&s,ModeStats*st=0) const; std::vector<ModeToken> tokenizeTemplate(const std::string&s,ModeStats*st=0) const; }; }
