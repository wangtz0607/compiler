#pragma once

#include <cstddef>
#include <functional>
#include <string>

#include "utils/Hash.h"

namespace ir {

struct Symbol {
    enum class Scope {
        kGlobal,
        kLocal,
    };

    Scope scope;
    std::string name;
};

inline bool operator==(const Symbol &lhs, const Symbol &rhs) {
    return lhs.scope == rhs.scope && lhs.name == rhs.name;
}

} // namespace ir

template <>
struct std::hash<ir::Symbol> {
    constexpr size_t operator()(const ir::Symbol &symbol) const noexcept {
        size_t seed = 0;

        hash_combine(seed, symbol.scope);
        hash_combine(seed, symbol.name);

        return seed;
    }
};
