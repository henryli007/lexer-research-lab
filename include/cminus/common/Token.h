#pragma once

#include <string>

namespace cminus {

enum class TokenType {
    Keyword,
    Identifier,
    Integer,
    Float,
    Operator,
    Separator,
    EndOfFile,
    Unknown
};

struct Token {
    std::string lexeme;
    TokenType type;
    std::string grammar;
    std::string attr;
    int line = 1;
    int column = 1;
};

inline std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::Keyword:
            return "KW";
        case TokenType::Identifier:
            return "IDN";
        case TokenType::Integer:
            return "INT";
        case TokenType::Float:
            return "FLOAT";
        case TokenType::Operator:
            return "OP";
        case TokenType::Separator:
            return "SE";
        case TokenType::EndOfFile:
            return "EOF";
        case TokenType::Unknown:
            return "UNKNOWN";
    }
    return "UNKNOWN";
}

} // namespace cminus
