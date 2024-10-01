#pragma once

#include <utility>

namespace ir {

enum class Attribute {
#define X(enumerator, specifier) k##enumerator,
#include "ir/Attribute.def"
#undef X
};

inline constexpr const char *specifier(Attribute attr) {
    using enum Attribute;
    switch (attr) {
#define X(enumerator, specifier) case k##enumerator: return specifier;
#include "ir/Attribute.def"
#undef X
    default:
        std::unreachable();
    }
}

} // namespace ir
