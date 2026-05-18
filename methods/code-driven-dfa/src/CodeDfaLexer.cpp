#include "codedfa/CodeDfaLexer.h"
#include "cminus/lexer/lexer.h"
namespace codedfa { cminus::LexResult CodeDfaLexer::tokenize(const std::string&s)const{ cminus::Lexer l; return l.tokenize(s); } }
