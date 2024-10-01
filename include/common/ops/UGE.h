#pragma once

#include <concepts>

#include "common/ops/ULT.h"

namespace ops {

struct UGE {
    template <typename T>
        requires std::integral<T>
    bool operator()(T x, T y) const {
        return !ULT()(x, y);
    }
};

} // namespace ops
