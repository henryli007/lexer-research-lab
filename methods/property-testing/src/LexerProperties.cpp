#include "proptest/LexerProperties.h"
#include "cminus/lexer/lexer.h"
namespace proptest {
std::vector<PropertyOutcome> checkProperties(const std::string& source,const cminus::LexResult& r,double ms){std::vector<PropertyOutcome> out;out.push_back(PropertyOutcome{"NoInfiniteLoop",ms<1000.0});
 bool mono=true;int pl=1,pc=0;for(size_t i=0;i<r.tokens.size();++i){if(r.tokens[i].line<pl||(r.tokens[i].line==pl&&r.tokens[i].column<pc))mono=false;pl=r.tokens[i].line;pc=r.tokens[i].column;}out.push_back(PropertyOutcome{"TokenOffsetsMonotonic",mono});
 bool longest=true;for(size_t i=0;i+1<r.tokens.size();++i){std::string a=r.tokens[i].lexeme,b=r.tokens[i+1].lexeme;if((a=="="&&b=="=")||(a=="<"&&b=="=")||(a==">"&&b=="=")||(a=="!"&&b=="="))longest=false;}out.push_back(PropertyOutcome{"LongestMatchOperators",longest});
 bool invisible=true;if(source.find("hidden")!=std::string::npos){for(size_t i=0;i<r.tokens.size();++i)if(r.tokens[i].lexeme=="hidden")invisible=false;}out.push_back(PropertyOutcome{"CommentsInvisible",invisible});
 bool kw=true;for(size_t i=0;i<r.tokens.size();++i){std::string x=r.tokens[i].lexeme;if((x=="int"||x=="float"||x=="void"||x=="if"||x=="else"||x=="while"||x=="return"||x=="const")&&r.tokens[i].type!=cminus::TokenType::Keyword)kw=false;}out.push_back(PropertyOutcome{"KeywordPriority",kw});
 bool locality=true;if(!r.diagnostics.empty()){bool hasEof=r.tokens.size()>0&&r.tokens.back().type==cminus::TokenType::EndOfFile;locality=hasEof;}out.push_back(PropertyOutcome{"ErrorLocality",locality});
 bool round=true;if(r.success){std::string rebuilt;for(size_t i=0;i<r.tokens.size();++i)if(r.tokens[i].type!=cminus::TokenType::EndOfFile){if(!rebuilt.empty())rebuilt+=" ";rebuilt+=r.tokens[i].lexeme;}cminus::Lexer l;cminus::LexResult rr=l.tokenize(rebuilt);size_t a=0,b=0;while(a<r.tokens.size()&&r.tokens[a].type!=cminus::TokenType::EndOfFile){while(b<rr.tokens.size()&&rr.tokens[b].type==cminus::TokenType::EndOfFile)b++;if(b>=rr.tokens.size()||r.tokens[a].type!=rr.tokens[b].type){round=false;break;}a++;b++;}}out.push_back(PropertyOutcome{"RoundTripTokenTypeStability",round});return out;}
}
