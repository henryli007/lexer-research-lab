#pragma once
#include <string>
#include <vector>
namespace tdfa { struct TaggedMatch { bool matched; std::string token; std::vector<std::string> groups; int tagOperations; std::string rawContent; std::vector<int> escapePositions; }; }
