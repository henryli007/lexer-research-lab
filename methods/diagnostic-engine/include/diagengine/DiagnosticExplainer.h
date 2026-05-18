#pragma once
#include "cminus/common/Diagnostic.h"
#include "diagengine/DiagnosticExplanation.h"
namespace diagengine { class DiagnosticExplainer { public: DiagnosticExplanation explain(const cminus::Diagnostic& d,const std::string& source) const; }; }
