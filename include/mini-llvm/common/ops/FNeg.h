#pragma once

#include <concepts>

namespace mini_llvm::ops {

struct FNeg {
    template <typename T>
        requires std::floating_point<T>
    T operator()(T x) const {
        return -x;
    }
};

} // namespace mini_llvm::ops
