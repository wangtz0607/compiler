#pragma once

#include <concepts>

namespace ops {

struct FNeg {
    template <typename T>
        requires std::floating_point<T>
    T operator()(T x) const {
        return -x;
    }
};

} // namespace ops
