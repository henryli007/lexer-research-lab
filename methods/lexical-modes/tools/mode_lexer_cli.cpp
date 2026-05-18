#include "modes/ModeLexer.h"
#include <fstream>
#include <iostream>
#include <sstream>
static std::string readf(const std::string&p){std::ifstream i(p.c_str(),std::ios::binary);std::ostringstream s;s<<i.rdbuf();return s.str();}
int main(int argc,char**argv){if(argc!=3){std::cerr<<"Usage: "<<argv[0]<<" <file> --template|--cminus\n";return 1;}std::string src=readf(argv[1]);modes::ModeLexer l;modes::ModeStats st={0,0,0};std::vector<modes::ModeToken> ts=std::string(argv[2])=="--template"?l.tokenizeTemplate(src,&st):l.tokenizeCminus(src,&st);std::cout<<"line,column,mode,token_type,lexeme,mode_transition\n";for(size_t i=0;i<ts.size();++i)std::cout<<ts[i].line<<","<<ts[i].column<<","<<ts[i].mode<<","<<ts[i].type<<","<<ts[i].lexeme<<","<<ts[i].transition<<"\n";}
