#pragma once
#include "modes/LexMode.h"
#include <vector>
namespace modes { class ModeStack { public: explicit ModeStack(LexMode initial); LexMode current() const; void push(LexMode m); void pop(); private: std::vector<LexMode> stack_; }; }
