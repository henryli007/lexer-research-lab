#pragma once
#include <string>
namespace roundtrip { struct Result { size_t tokens; size_t printedBytes; bool typeStable; bool lexemeStable; long long elapsedUs; std::string reason; }; class RoundTripChecker { public: Result check(const std::string& source) const; }; }
