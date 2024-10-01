#pragma once

#include <concepts>

#include "common/ops/UGT.h"

namespace ops {

struct ULE {
    template <typename T>
        requires std::integral<T>
    bool operator()(T x, T y) const {
        return !UGT()(x, y);
    }
};

} // namespace ops
