#pragma once
#include <string>
namespace incremental {
enum class EditType { Insert, Delete, Replace };
struct EditOperation { std::string name; EditType type; size_t offset; size_t length; std::string text; };
bool parseEditJsonLine(const std::string& line, EditOperation& out);
std::string editTypeName(EditType type);
}
