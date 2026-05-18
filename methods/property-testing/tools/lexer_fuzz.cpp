#include "proptest/SourceGenerator.h"
#include "proptest/LexerProperties.h"
#include "cminus/lexer/lexer.h"
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
int main(int argc,char**argv){int cases=1000;unsigned seed=42;for(int i=1;i+1<argc;i+=2){std::string a=argv[i];if(a=="--cases")cases=std::atoi(argv[i+1]);else if(a=="--seed")seed=(unsigned)std::strtoul(argv[i+1],0,10);}proptest::SourceGenerator gen(seed);std::map<std::string,int> pass,fail;int totalPass=0,totalFail=0;for(int i=0;i<cases;++i){std::string src=gen.next();cminus::Lexer l;auto t0=std::chrono::high_resolution_clock::now();cminus::LexResult r=l.tokenize(src);auto t1=std::chrono::high_resolution_clock::now();double ms=std::chrono::duration<double,std::milli>(t1-t0).count();std::vector<proptest::PropertyOutcome> os=proptest::checkProperties(src,r,ms);for(size_t j=0;j<os.size();++j){if(os[j].pass){pass[os[j].name]++;totalPass++;}else{fail[os[j].name]++;totalFail++;std::ofstream f(("methods/property-testing/failing_cases/"+os[j].name+"_"+std::to_string(seed)+"_"+std::to_string(i)+".sy").c_str());f<<src;}}}std::ofstream out("results/raw/property_fuzz_results.csv");out<<"seed,cases,total_pass,total_fail,property,pass_count,fail_count\n";for(std::map<std::string,int>::const_iterator it=pass.begin();it!=pass.end();++it)out<<seed<<","<<cases<<","<<totalPass<<","<<totalFail<<","<<it->first<<","<<it->second<<","<<fail[it->first]<<"\n";return 0;}
