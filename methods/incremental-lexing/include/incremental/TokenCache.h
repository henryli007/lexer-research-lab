#pragma once
#include "cminus/common/Token.h"
#include <vector>
namespace incremental {
enum class LexMode { NORMAL, LINE_COMMENT, BLOCK_COMMENT };
struct CachedToken { cminus::Token token; size_t startOffset; size_t endOffset; int startLine; int startColumn; int endLine; int endColumn; LexMode startMode; LexMode endMode; };
std::vector<CachedToken> buildTokenCache(const std::string& source, const std::vector<cminus::Token>& tokens);
}
