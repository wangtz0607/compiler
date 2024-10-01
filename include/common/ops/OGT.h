#pragma once

#include <cmath>
#include <concepts>

namespace ops {

struct OGT {
    template <typename T>
        requires std::floating_point<T>
    bool operator()(T x, T y) const {
        return std::isgreater(x, y);
    }
};

} // namespace ops
