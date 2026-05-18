#include "roundtrip/RoundTripChecker.h"
#include <fstream>
#include <iostream>
#include <sstream>
static std::string readf(const std::string&p){std::ifstream i(p.c_str(),std::ios::binary);std::ostringstream s;s<<i.rdbuf();return s.str();}
int main(int argc,char**argv){if(argc!=2)return 1;std::string s=readf(argv[1]);roundtrip::RoundTripChecker c;roundtrip::Result r=c.check(s);std::ifstream chk("results/raw/roundtrip_results.csv",std::ios::binary|std::ios::ate);bool empty=!chk||chk.tellg()==0;std::ofstream o("results/raw/roundtrip_results.csv",std::ios::app);if(empty)o<<"file,input_bytes,tokens,printed_bytes,type_stable,lexeme_stable,elapsed_us,fail_reason\n";o<<argv[1]<<","<<s.size()<<","<<r.tokens<<","<<r.printedBytes<<","<<(r.typeStable?"true":"false")<<","<<(r.lexemeStable?"true":"false")<<","<<r.elapsedUs<<","<<r.reason<<"\n";return r.typeStable?0:1;}
