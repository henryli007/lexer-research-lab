#include "derivative/RegexAst.h"
#include <sstream>
namespace derivative {
RegexPtr emptySet(){ return RegexPtr(new Regex(Kind::EmptySet)); }
RegexPtr epsilon(){ return RegexPtr(new Regex(Kind::Epsilon)); }
RegexPtr literal(char ch){ RegexPtr r(new Regex(Kind::LiteralChar)); r->literal=ch; return r; }
RegexPtr charClass(const std::string& chars){ RegexPtr r(new Regex(Kind::CharClass)); r->chars.insert(chars.begin(), chars.end()); return r; }
RegexPtr concat(RegexPtr a, RegexPtr b){ RegexPtr r(new Regex(Kind::Concat)); r->left=a; r->right=b; return r; }
RegexPtr alt(RegexPtr a, RegexPtr b){ RegexPtr r(new Regex(Kind::Alt)); r->left=a; r->right=b; return r; }
RegexPtr star(RegexPtr a){ RegexPtr r(new Regex(Kind::Star)); r->left=a; return r; }
RegexPtr plus(RegexPtr a){ return concat(a, star(a)); }
RegexPtr optional(RegexPtr a){ return alt(a, epsilon()); }
std::string canonical(const RegexPtr& r){ std::ostringstream o; switch(r->kind){case Kind::EmptySet:o<<"0";break;case Kind::Epsilon:o<<"1";break;case Kind::LiteralChar:o<<"'"<<r->literal<<"'";break;case Kind::CharClass:o<<"[";for(std::set<char>::const_iterator i=r->chars.begin();i!=r->chars.end();++i)o<<*i;o<<"]";break;case Kind::Concat:o<<"("<<canonical(r->left)<<"."<<canonical(r->right)<<")";break;case Kind::Alt:o<<"("<<canonical(r->left)<<"|"<<canonical(r->right)<<")";break;case Kind::Star:o<<"("<<canonical(r->left)<<")*";break;} return o.str(); }
}
