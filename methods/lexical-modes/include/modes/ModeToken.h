#pragma once
#include <string>
namespace modes { struct ModeToken { int line; int column; std::string mode; std::string type; std::string lexeme; std::string transition; }; }
