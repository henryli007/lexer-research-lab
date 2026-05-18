from __future__ import print_function
import os, shutil, subprocess, sys
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD=os.path.join(ROOT,"build")
CXX=os.environ.get("CXX","g++")
BASE=["-std=c++11","-Wall","-Wextra","-Iinclude"]
TARGETS={
 "baseline":("lexer_cli",["tools/lexer_cli.cpp","src/lexer/lexer.cpp","src/lexer/automata.cpp"],[]),
 "derivative":("derivative_lexer_cli",["methods/regex-derivative/tools/derivative_lexer_cli.cpp","methods/regex-derivative/src/RegexAst.cpp","methods/regex-derivative/src/Derivative.cpp","methods/regex-derivative/src/Simplify.cpp","methods/regex-derivative/src/DerivativeLexer.cpp"],["-Imethods/regex-derivative/include"]),
 "incremental":("incremental_bench",["methods/incremental-lexing/tools/incremental_bench.cpp","methods/incremental-lexing/src/EditScript.cpp","methods/incremental-lexing/src/TokenCache.cpp","methods/incremental-lexing/src/IncrementalLexer.cpp","src/lexer/lexer.cpp","src/lexer/automata.cpp"],["-Imethods/incremental-lexing/include"]),
 "fuzz":("lexer_fuzz",["methods/property-testing/tools/lexer_fuzz.cpp","methods/property-testing/src/SourceGenerator.cpp","methods/property-testing/src/LexerProperties.cpp","src/lexer/lexer.cpp","src/lexer/automata.cpp"],["-Imethods/property-testing/include"]),
 "automata":("automata_stats_dump",["methods/automata-visualization/tools/automata_stats_dump.cpp","src/lexer/automata.cpp"],[]),
 "automata-dot":("export_automata_dot",["methods/automata-visualization/tools/export_automata_dot.cpp","src/lexer/automata.cpp"],[]),
 "modes":("mode_lexer_cli",["methods/lexical-modes/tools/mode_lexer_cli.cpp","methods/lexical-modes/src/ModeStack.cpp","methods/lexical-modes/src/ModeLexer.cpp"],["-Imethods/lexical-modes/include"]),
 "tdfa":("tdfa_demo",["methods/tdfa/tools/tdfa_demo.cpp","methods/tdfa/src/TaggedDFA.cpp"],["-Imethods/tdfa/include"]),
 "code-dfa":("code_dfa_bench",["methods/code-driven-dfa/tools/code_dfa_bench.cpp","methods/code-driven-dfa/src/CodeDfaLexer.cpp","src/lexer/lexer.cpp","src/lexer/automata.cpp"],["-Imethods/code-driven-dfa/include"]),
 "diagnostics":("diagnostic_demo",["methods/diagnostic-engine/tools/diagnostic_demo.cpp","methods/diagnostic-engine/src/DiagnosticExplainer.cpp","src/lexer/lexer.cpp","src/lexer/automata.cpp"],["-Imethods/diagnostic-engine/include"]),
 "roundtrip":("roundtrip_check",["methods/roundtrip/tools/roundtrip_check.cpp","methods/roundtrip/src/TokenPrinter.cpp","methods/roundtrip/src/RoundTripChecker.cpp","src/lexer/lexer.cpp","src/lexer/automata.cpp"],["-Imethods/roundtrip/include"]),
}
ORDER=["baseline","derivative","incremental","fuzz","automata","automata-dot","modes","tdfa","code-dfa","diagnostics","roundtrip"]
def build(name):
    if not os.path.isdir(BUILD): os.makedirs(BUILD)
    out,srcs,extra=TARGETS[name]
    subprocess.check_call([CXX]+BASE+extra+srcs+["-o",os.path.join(BUILD,out+(".exe" if os.name=="nt" else ""))],cwd=ROOT)
def main():
    arg=sys.argv[1] if len(sys.argv)>1 else "all"
    if arg=="clean":
        if os.path.isdir(BUILD): shutil.rmtree(BUILD)
        return
    for name in (ORDER if arg=="all" else [arg]): build(name)
if __name__=="__main__": main()
