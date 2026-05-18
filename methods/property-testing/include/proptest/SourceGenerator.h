#pragma once
#include <random>
#include <string>
namespace proptest { class SourceGenerator { public: explicit SourceGenerator(unsigned seed); std::string next(); private: std::mt19937 rng_; }; }
