#pragma once

#include <cmath>
#include <concepts>

namespace ops {

struct OEQ {
    template <typename T>
        requires std::floating_point<T>
    bool operator()(T x, T y) const {
        return !std::isunordered(x, y) && x == y;
    }
};

} // namespace ops
