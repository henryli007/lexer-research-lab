#include "roundtrip/RoundTripChecker.h"
#include "roundtrip/TokenPrinter.h"
#include "cminus/lexer/lexer.h"
#include <chrono>
namespace roundtrip { Result RoundTripChecker::check(const std::string&s)const{auto t0=std::chrono::high_resolution_clock::now();cminus::Lexer l;cminus::LexResult a=l.tokenize(s);Result r={a.tokens.size(),0,false,false,0,""};if(!a.success){r.reason="source has diagnostics";return r;}TokenPrinter p;std::string out=p.print(a.tokens);cminus::LexResult b=l.tokenize(out);r.printedBytes=out.size();r.typeStable=a.tokens.size()==b.tokens.size();r.lexemeStable=r.typeStable;for(size_t i=0;i<a.tokens.size()&&r.typeStable;++i){if(a.tokens[i].type!=b.tokens[i].type)r.typeStable=false;if(a.tokens[i].lexeme!=b.tokens[i].lexeme)r.lexemeStable=false;}r.reason=(r.typeStable&&r.lexemeStable)?"ok":"token mismatch";r.elapsedUs=std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t0).count();return r;} }
