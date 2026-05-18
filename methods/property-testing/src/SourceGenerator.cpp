#include "proptest/SourceGenerator.h"
namespace proptest {
SourceGenerator::SourceGenerator(unsigned seed):rng_(seed){}
std::string SourceGenerator::next(){static const char* parts[]={"int","float","void","if","else","while","return","const","alpha","beta_2","123","45.67","+","-","*","/","==","<=",">=","!=","&&","||","!","(",")","{","}",";",","," ","\n","// hidden comment\n","/* block hidden */","/* unterminated","@","，","12abc","1.","1..2","&&&"};std::uniform_int_distribution<int> n(4,20),pick(0,(int)(sizeof(parts)/sizeof(parts[0])-1));std::string s;int count=n(rng_);for(int i=0;i<count;++i){s+=parts[pick(rng_)];if(i+1<count)s+=" ";}return s;}
}
