#pragma once

#include <cmath>
#include <concepts>

namespace mini_llvm::ops {

struct OEQ {
    template <typename T>
        requires std::floating_point<T>
    bool operator()(T x, T y) const {
        return !std::isunordered(x, y) && x == y;
    }
};

} // namespace mini_llvm::ops
