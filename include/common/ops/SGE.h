#pragma once

#include <concepts>

#include "common/ops/SLT.h"

namespace ops {

struct SGE {
    template <typename T>
        requires std::integral<T>
    bool operator()(T x, T y) const {
        return !SLT()(x, y);
    }
};

} // namespace ops
