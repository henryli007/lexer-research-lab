#pragma once
#include "tdfa/TaggedMatch.h"
namespace tdfa { class TaggedDFA { public: TaggedMatch matchFloat(const std::string&s)const; TaggedMatch matchString(const std::string&s)const; }; }
