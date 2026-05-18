#include "incremental/EditScript.h"
#include <cstdlib>
namespace incremental {
static std::string value(const std::string&s,const std::string&k){std::string q="\""+k+"\":\"";size_t p=s.find(q);if(p==std::string::npos)return "";p+=q.size();size_t e=s.find('"',p);return s.substr(p,e-p);}
static size_t num(const std::string&s,const std::string&k){std::string q="\""+k+"\":";size_t p=s.find(q);if(p==std::string::npos)return 0;p+=q.size();return (size_t)std::strtoul(s.c_str()+p,0,10);}
bool parseEditJsonLine(const std::string& line, EditOperation& out){out.name=value(line,"name");std::string t=value(line,"type");out.type=t=="insert"?EditType::Insert:t=="delete"?EditType::Delete:EditType::Replace;out.offset=num(line,"offset");out.length=num(line,"length");out.text=value(line,"text");return !out.name.empty();}
std::string editTypeName(EditType t){return t==EditType::Insert?"insert":t==EditType::Delete?"delete":"replace";}
}
