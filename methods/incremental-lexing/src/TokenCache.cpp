#include "incremental/TokenCache.h"
namespace incremental {
std::vector<CachedToken> buildTokenCache(const std::string& source,const std::vector<cminus::Token>& tokens){std::vector<CachedToken> out;size_t cursor=0;for(size_t i=0;i<tokens.size();++i){if(tokens[i].type==cminus::TokenType::EndOfFile)continue;size_t p=source.find(tokens[i].lexeme,cursor);if(p==std::string::npos)p=cursor;CachedToken c;c.token=tokens[i];c.startOffset=p;c.endOffset=p+tokens[i].lexeme.size();c.startLine=tokens[i].line;c.startColumn=tokens[i].column;c.endLine=tokens[i].line;c.endColumn=tokens[i].column+(int)tokens[i].lexeme.size();c.startMode=LexMode::NORMAL;c.endMode=LexMode::NORMAL;out.push_back(c);cursor=c.endOffset;}return out;}
}
