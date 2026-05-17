#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "cminus/common/Diagnostic.h"
#include "cminus/common/Token.h"
#include "cminus/lexer/automata.h"
#include "cminus/lexer/lexer.h"

namespace {

std::string readTextFile(const std::string& path) {
    std::ifstream input(path.c_str(), std::ios::in | std::ios::binary);
    if (!input) {
        throw std::runtime_error("cannot open file: " + path);
    }

    std::ostringstream buffer;
    buffer << input.rdbuf();
    return buffer.str();
}

void writeTokenTable(const std::vector<cminus::Token>& tokens, std::ostream& output) {
    output << "line\tcolumn\ttype\tgrammar\tattr\tlexeme\n";
    for (size_t i = 0; i < tokens.size(); i++) {
        const cminus::Token& token = tokens[i];
        output << token.line << '\t'
               << token.column << '\t'
               << cminus::tokenTypeToString(token.type) << '\t'
               << token.grammar << '\t'
               << token.attr << '\t'
               << token.lexeme << '\n';
    }
}

void writeStats(std::ostream& output) {
    cminus::AutomataStats stats = cminus::getAutomataStats();
    output << "rules=" << stats.rules
           << ", alphabet=" << stats.alphabetSize
           << ", nfa_states=" << stats.nfaStates
           << ", dfa_states=" << stats.dfaStates
           << ", minimized_dfa_states=" << stats.minimizedDfaStates
           << '\n';
}

} // namespace

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input.sy>\n";
        return 1;
    }

    try {
        std::string source = readTextFile(argv[1]);

        cminus::Lexer lexer;
        cminus::LexResult result = lexer.tokenize(source);

        writeTokenTable(result.tokens, std::cout);

        if (std::getenv("LEXER_STATS") != NULL) {
            writeStats(std::cerr);
        }

        if (!result.success) {
            if (std::getenv("DIAGNOSTICS_JSON") != NULL) {
                std::cerr << cminus::renderDiagnosticsJsonLines(result.diagnostics);
            }
            std::cerr << result.errorMessage;
            return 1;
        }

        return 0;
    } catch (const std::exception& error) {
        std::cerr << "[lexer_cli] " << error.what() << '\n';
        return 1;
    }
}
