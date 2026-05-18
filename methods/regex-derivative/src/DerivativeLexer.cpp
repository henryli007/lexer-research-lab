#include "derivative/DerivativeLexer.h"
#include "derivative/Derivative.h"
#include <chrono>
#include <stdexcept>
#include <set>
namespace derivative {
namespace {
struct Rule { std::string name; RegexPtr regex; bool emit; };
std::string letters(){std::string s;for(char c='a';c<='z';++c)s+=c;for(char c='A';c<='Z';++c)s+=c;s+="_";return s;}
std::string digits(){return "0123456789";}
std::vector<Rule> rules(){ std::string l=letters(), d=digits(); std::string ld=l+d; std::vector<Rule> r;
 r.push_back(Rule{"FLOAT", concat(plus(charClass(d)), concat(literal('.'), plus(charClass(d)))), true});
 r.push_back(Rule{"ID", concat(charClass(l), star(charClass(ld))), true});
 r.push_back(Rule{"INT", plus(charClass(d)), true});
 r.push_back(Rule{"WS", plus(charClass(" \t\r\n")), false});
 const char* ops[]={"==","<=",">=","!=","+","-","*","/","=","<",">",0}; for(int i=0;ops[i];++i){ RegexPtr x=literal(ops[i][0]); if(ops[i][1]) x=concat(x,literal(ops[i][1])); r.push_back(Rule{"OP",x,true});}
 const char* ds="(){};,"; for(int i=0;ds[i];++i) r.push_back(Rule{"DELIM",literal(ds[i]),true}); return r; }
bool keyword(const std::string& s){ static const char* ks[]={"int","float","void","if","else","while","return","const",0}; for(int i=0;ks[i];++i) if(s==ks[i]) return true; return false; }
}
std::vector<Token> DerivativeLexer::tokenize(const std::string& source, Stats* stats) const{
 auto begin=std::chrono::high_resolution_clock::now(); std::vector<Token> out; std::vector<Rule> rs=rules(); size_t pos=0,steps=0; std::set<std::string> states; int line=1,col=1;
 while(pos<source.size()){ size_t best=0; int bestRule=-1; for(size_t i=0;i<rs.size();++i){ size_t len=matchPrefix(rs[i].regex,source,pos,&steps,&states); if(len>best){best=len;bestRule=(int)i;} }
  if(best==0) throw std::runtime_error("unsupported character at byte "+std::to_string((unsigned long long)pos));
  std::string lex=source.substr(pos,best); if(rs[bestRule].emit){ std::string type=rs[bestRule].name; if(type=="ID"&&keyword(lex)) type="KEYWORD"; out.push_back(Token{line,col,type,lex});}
  for(size_t i=0;i<lex.size();++i){ if(lex[i]=='\n'){line++;col=1;} else col++; } pos+=best;
 }
 auto end=std::chrono::high_resolution_clock::now(); if(stats){stats->inputBytes=source.size();stats->tokens=out.size();stats->derivativeSteps=steps;stats->uniqueRegexStates=states.size();stats->elapsedMs=std::chrono::duration<double,std::milli>(end-begin).count();} return out;
}
}
