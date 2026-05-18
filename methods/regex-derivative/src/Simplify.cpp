#include "derivative/Simplify.h"
namespace derivative {
RegexPtr simplify(const RegexPtr& r){
 if(r->kind==Kind::Concat){ RegexPtr a=simplify(r->left), b=simplify(r->right); if(a->kind==Kind::EmptySet||b->kind==Kind::EmptySet)return emptySet(); if(a->kind==Kind::Epsilon)return b; if(b->kind==Kind::Epsilon)return a; return concat(a,b);}
 if(r->kind==Kind::Alt){ RegexPtr a=simplify(r->left), b=simplify(r->right); if(a->kind==Kind::EmptySet)return b; if(b->kind==Kind::EmptySet)return a; if(canonical(a)==canonical(b))return a; if(canonical(a)>canonical(b)){RegexPtr t=a;a=b;b=t;} return alt(a,b);}
 if(r->kind==Kind::Star){ RegexPtr a=simplify(r->left); if(a->kind==Kind::EmptySet||a->kind==Kind::Epsilon)return epsilon(); if(a->kind==Kind::Star)return a; return star(a);}
 return r;
}
}
