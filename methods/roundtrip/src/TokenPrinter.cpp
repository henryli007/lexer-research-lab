#include "roundtrip/TokenPrinter.h"
namespace roundtrip { std::string TokenPrinter::print(const std::vector<cminus::Token>& t)const{std::string s;for(size_t i=0;i<t.size();++i)if(t[i].type!=cminus::TokenType::EndOfFile){if(!s.empty())s+=" ";s+=t[i].lexeme;}return s;} }
