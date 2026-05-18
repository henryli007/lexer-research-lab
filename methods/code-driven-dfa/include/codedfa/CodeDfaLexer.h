#pragma once
#include "cminus/common/LexResult.h"
namespace codedfa { class CodeDfaLexer { public: cminus::LexResult tokenize(const std::string&s) const; }; }
