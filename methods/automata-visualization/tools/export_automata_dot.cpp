#include "cminus/lexer/automata.h"
#include <cstdlib>
#include <iostream>
int main(){cminus::exportNfaDot("methods/automata-visualization/dot/nfa.dot");cminus::exportDfaDot("methods/automata-visualization/dot/dfa.dot");cminus::exportMinDfaDot("methods/automata-visualization/dot/min_dfa.dot");int a=std::system("dot -Tsvg methods/automata-visualization/dot/min_dfa.dot -o results/figures/min_dfa.svg");int b=std::system("dot -Tpdf methods/automata-visualization/dot/min_dfa.dot -o results/figures/min_dfa.pdf");if(a!=0||b!=0)std::cout<<"Graphviz not found; DOT files were generated but SVG rendering was skipped.\n";return 0;}
