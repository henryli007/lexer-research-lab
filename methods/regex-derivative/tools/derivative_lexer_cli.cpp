#include "derivative/DerivativeLexer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
static std::string readFile(const std::string& p){std::ifstream in(p.c_str(),std::ios::binary);if(!in)throw std::runtime_error("cannot open file: "+p);std::ostringstream s;s<<in.rdbuf();return s.str();}
int main(int argc,char**argv){ if(argc<2||argc>3){std::cerr<<"Usage: "<<argv[0]<<" <input.sy> [--stats]\n";return 1;} try{std::string src=readFile(argv[1]); derivative::DerivativeLexer l; derivative::Stats st={0,0,0,0,0}; std::vector<derivative::Token> ts=l.tokenize(src,&st); if(argc==3&&std::string(argv[2])=="--stats"){std::cout<<"method,input_bytes,tokens,derivative_steps,unique_regex_states,elapsed_ms\nregex_derivative,"<<st.inputBytes<<","<<st.tokens<<","<<st.derivativeSteps<<","<<st.uniqueRegexStates<<","<<st.elapsedMs<<"\n";return 0;} std::cout<<"line,column,token_type,lexeme,method\n"; for(size_t i=0;i<ts.size();++i)std::cout<<ts[i].line<<","<<ts[i].column<<","<<ts[i].type<<","<<ts[i].lexeme<<",regex_derivative\n"; return 0;}catch(const std::exception&e){std::cerr<<"[derivative_lexer_cli] "<<e.what()<<"\n";return 1;}}
