#include "cminus/lexer/automata.h"
#include <iostream>
static int nfaEdges(const cminus::NFA& n){int e=0;for(size_t i=0;i<n.states.size();++i)e+=(int)n.states[i].edges.size();return e;}
static int dfaEdges(const cminus::DFA& d){int e=0;for(size_t i=0;i<d.states.size();++i)e+=(int)d.states[i].trans.size();return e;}
static int accepts(const cminus::DFA& d){int n=0;for(size_t i=0;i<d.states.size();++i)if(d.states[i].acceptRule>=0)n++;return n;}
int main(){const cminus::NFA& n=cminus::getLexerNFA();const cminus::DFA& d=cminus::getLexerDFA();const cminus::DFA& m=cminus::getMinimizedDFA();cminus::AutomataStats s=cminus::getAutomataStats();std::cout<<"automaton,states,edges,accept_states,rules,alphabet_size\n";std::cout<<"NFA,"<<n.states.size()<<","<<nfaEdges(n)<<",0,"<<s.rules<<","<<s.alphabetSize<<"\n";std::cout<<"DFA,"<<d.states.size()<<","<<dfaEdges(d)<<","<<accepts(d)<<","<<s.rules<<","<<s.alphabetSize<<"\n";std::cout<<"MinDFA,"<<m.states.size()<<","<<dfaEdges(m)<<","<<accepts(m)<<","<<s.rules<<","<<s.alphabetSize<<"\n";}
