#pragma once
#include "incremental/EditScript.h"
#include "incremental/TokenCache.h"
#include <string>
namespace incremental {
struct IncrementalResult { std::vector<cminus::Token> tokens; size_t reusedTokenCount; size_t totalOldTokenCount; size_t rescanStartOffset; size_t rescanEndOffset; size_t rescannedBytes; size_t fullBytes; double fullLexMs; double incrementalLexMs; bool equivalentToFullLex; };
class IncrementalLexer {
public:
 explicit IncrementalLexer(const std::string& source);
 IncrementalResult apply(const EditOperation& edit);
 const std::string& source() const { return source_; }
private:
 std::string source_;
 std::vector<cminus::Token> tokens_;
};
}
