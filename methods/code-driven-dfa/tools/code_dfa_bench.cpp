#include "codedfa/CodeDfaLexer.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
static std::string readf(const std::string&p){std::ifstream i(p.c_str(),std::ios::binary);std::ostringstream s;s<<i.rdbuf();return s.str();}
int main(int argc,char**argv){if(argc!=2)return 1;std::string s=readf(argv[1]);codedfa::CodeDfaLexer l;auto t0=std::chrono::high_resolution_clock::now();cminus::LexResult r=l.tokenize(s);auto us=std::max<long long>(1,std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-t0).count());std::ifstream g("methods/code-driven-dfa/generated/cminus_switch_lexer.cpp",std::ios::binary|std::ios::ate);size_t code=g?(size_t)g.tellg():0;std::ifstream chk("results/raw/code_dfa_results.csv",std::ios::binary|std::ios::ate);bool empty=!chk||chk.tellg()==0;std::ofstream o("results/raw/code_dfa_results.csv",std::ios::app);if(empty)o<<"file,input_bytes,tokens,elapsed_us,throughput_mb_s,code_size_bytes,success\n";double mb=s.size()/1024.0/1024.0;o<<argv[1]<<","<<s.size()<<","<<r.tokens.size()<<","<<us<<","<<(mb/(us/1000000.0))<<","<<code<<","<<(r.success?"true":"false")<<"\n";return r.success?0:1;}
