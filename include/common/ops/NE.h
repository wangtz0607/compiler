#pragma once

#include <concepts>

namespace ops {

struct NE {
    template <typename T>
        requires std::integral<T>
    bool operator()(T x, T y) const {
        return x != y;
    }
};

} // namespace ops
