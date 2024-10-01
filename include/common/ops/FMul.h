#pragma once

#include <concepts>

namespace ops {

struct FMul {
    template <typename T>
        requires std::floating_point<T>
    T operator()(T x, T y) const {
        return x * y;
    }
};

} // namespace ops
