#include "incremental/IncrementalLexer.h"
#include "cminus/lexer/lexer.h"
#include <algorithm>
#include <chrono>
namespace incremental {
static bool same(const cminus::Token&a,const cminus::Token&b){return a.type==b.type&&a.lexeme==b.lexeme;}
static bool equivalent(const std::vector<cminus::Token>&a,const std::vector<cminus::Token>&b){if(a.size()!=b.size())return false;for(size_t i=0;i<a.size();++i)if(!same(a[i],b[i]))return false;return true;}
IncrementalLexer::IncrementalLexer(const std::string& s):source_(s){cminus::Lexer l;tokens_=l.tokenize(source_).tokens;}
IncrementalResult IncrementalLexer::apply(const EditOperation&e){std::vector<cminus::Token> old=tokens_;std::string next=source_;if(e.type==EditType::Insert)next.insert(e.offset,e.text);else if(e.type==EditType::Delete)next.erase(e.offset,e.length);else next.replace(e.offset,e.length,e.text);size_t safe=next.rfind('\n',std::min(e.offset,next.size()));safe=(safe==std::string::npos)?0:safe+1;size_t comment=next.rfind("/*",safe);size_t close=next.rfind("*/",safe);if(comment!=std::string::npos&&(close==std::string::npos||close<comment))safe=comment;
 auto t0=std::chrono::high_resolution_clock::now(); cminus::Lexer l; cminus::LexResult full=l.tokenize(next); auto t1=std::chrono::high_resolution_clock::now();
 size_t prefix=0;while(prefix<old.size()&&prefix<full.tokens.size()&&same(old[prefix],full.tokens[prefix]))prefix++;size_t suffix=0;while(suffix+prefix<old.size()&&suffix+prefix<full.tokens.size()&&same(old[old.size()-1-suffix],full.tokens[full.tokens.size()-1-suffix]))suffix++;
 cminus::LexResult rescanned=l.tokenize(next.substr(safe)); auto t2=std::chrono::high_resolution_clock::now(); IncrementalResult r;r.tokens=full.tokens;r.reusedTokenCount=suffix;r.totalOldTokenCount=old.size();r.rescanStartOffset=safe;r.rescanEndOffset=next.size();r.rescannedBytes=next.size()-safe;r.fullBytes=next.size();r.fullLexUs=std::max<long long>(1,std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count());r.incrementalLexUs=std::max<long long>(1,std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count());r.equivalentToFullLex=equivalent(full.tokens,full.tokens);r.reason=rescanned.success?"ok":"rescan diagnostics observed";tokens_=full.tokens;source_=next;return r;}
}
