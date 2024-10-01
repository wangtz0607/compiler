#pragma once

#include <concepts>

#include "common/ops/SGT.h"

namespace ops {

struct SLE {
    template <typename T>
        requires std::integral<T>
    bool operator()(T x, T y) const {
        return !SGT()(x, y);
    }
};

} // namespace ops
