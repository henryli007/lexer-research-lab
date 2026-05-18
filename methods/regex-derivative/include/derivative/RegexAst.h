#pragma once
#include <memory>
#include <set>
#include <string>

namespace derivative {
enum class Kind { EmptySet, Epsilon, LiteralChar, CharClass, Concat, Alt, Star };
struct Regex;
typedef std::shared_ptr<Regex> RegexPtr;
struct Regex {
    Kind kind;
    char literal;
    std::set<char> chars;
    RegexPtr left;
    RegexPtr right;
    explicit Regex(Kind k) : kind(k), literal(0) {}
};
RegexPtr emptySet();
RegexPtr epsilon();
RegexPtr literal(char ch);
RegexPtr charClass(const std::string& chars);
RegexPtr concat(RegexPtr a, RegexPtr b);
RegexPtr alt(RegexPtr a, RegexPtr b);
RegexPtr star(RegexPtr a);
RegexPtr plus(RegexPtr a);
RegexPtr optional(RegexPtr a);
std::string canonical(const RegexPtr& r);
}
