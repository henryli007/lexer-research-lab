#pragma once
namespace modes { enum class LexMode { NORMAL, LINE_COMMENT, BLOCK_COMMENT, STRING, TEMPLATE_TEXT, TEMPLATE_EXPR }; const char* modeName(LexMode m); }
