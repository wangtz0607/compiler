#pragma once

#include <utility>

namespace mir {

enum class Condition {
#define X(enumerator, specifier) k##enumerator,
#include "mir/Condition.def"
#undef X
};

inline constexpr const char *specifier(Condition cond) {
    switch (cond) {
#define X(enumerator, specifier) case Condition::k##enumerator: return specifier;
#include "mir/Condition.def"
#undef X
    default:
        std::unreachable();
    }
}

} // namespace mir
