#pragma once

#include <cmath>
#include <concepts>

namespace mini_llvm::ops {

struct FRem {
    template <typename T>
        requires std::floating_point<T>
    T operator()(T x, T y) const {
        return std::fmod(x, y);
    }
};

} // namespace mini_llvm::ops
