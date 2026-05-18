from __future__ import print_function
import os, shutil, subprocess, sys
ROOT=os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD=os.path.join(ROOT,"build")
CXX=os.environ.get("CXX","g++")
BASE=["-std=c++11","-Wall","-Wextra","-Iinclude"]
TARGETS={
"baseline":["tools/lexer_cli.cpp","src/lexer/lexer.cpp","src/lexer/automata.cpp"],
"derivative":["methods/regex-derivative/tools/derivative_lexer_cli.cpp","methods/regex-derivative/src/RegexAst.cpp","methods/regex-derivative/src/Derivative.cpp","methods/regex-derivative/src/Simplify.cpp","methods/regex-derivative/src/DerivativeLexer.cpp"],
"incremental":["methods/incremental-lexing/tools/incremental_bench.cpp","methods/incremental-lexing/src/EditScript.cpp","methods/incremental-lexing/src/TokenCache.cpp","methods/incremental-lexing/src/IncrementalLexer.cpp","src/lexer/lexer.cpp","src/lexer/automata.cpp"],
"fuzz":["methods/property-testing/tools/lexer_fuzz.cpp","methods/property-testing/src/SourceGenerator.cpp","methods/property-testing/src/LexerProperties.cpp","src/lexer/lexer.cpp","src/lexer/automata.cpp"],
"automata-viz":["methods/automata-visualization/tools/export_automata_dot.cpp","src/lexer/automata.cpp"],
"automata-stats":["methods/automata-visualization/tools/automata_stats_dump.cpp","src/lexer/automata.cpp"],
}
OUT={"baseline":"lexer_cli","derivative":"derivative_lexer_cli","incremental":"incremental_bench","fuzz":"lexer_fuzz","automata-viz":"export_automata_dot","automata-stats":"automata_stats_dump"}
EXTRA={"derivative":["-Imethods/regex-derivative/include"],"incremental":["-Imethods/incremental-lexing/include"],"fuzz":["-Imethods/property-testing/include"]}
def build(name):
    if not os.path.isdir(BUILD): os.makedirs(BUILD)
    out=os.path.join(BUILD,OUT[name]+(".exe" if os.name=="nt" else ""))
    cmd=[CXX]+BASE+EXTRA.get(name,[])+TARGETS[name]+["-o",out]
    subprocess.check_call(cmd,cwd=ROOT)
def main():
    arg=sys.argv[1] if len(sys.argv)>1 else "all"
    if arg=="clean":
        if os.path.isdir(BUILD): shutil.rmtree(BUILD)
        return
    names=list(TARGETS) if arg=="all" else [arg]
    for n in names: build(n)
if __name__=="__main__": main()
