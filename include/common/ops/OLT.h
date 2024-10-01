#pragma once

#include <cmath>
#include <concepts>

namespace ops {

struct OLT {
    template <typename T>
        requires std::floating_point<T>
    bool operator()(T x, T y) const {
        return std::isless(x, y);
    }
};

} // namespace ops
