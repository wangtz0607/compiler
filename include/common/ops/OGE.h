#pragma once

#include <cmath>
#include <concepts>

namespace ops {

struct OGE {
    template <typename T>
        requires std::floating_point<T>
    bool operator()(T x, T y) const {
        return std::isgreaterequal(x, y);
    }
};

} // namespace ops
