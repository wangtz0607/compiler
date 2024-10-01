#pragma once

#include <bit>
#include <concepts>
#include <type_traits>

#include "common/OpException.h"

namespace ops {

struct UDiv {
    template <typename T>
        requires std::integral<T>
    T operator()(T x, T y) const {
        if (y == 0)
            throw OpException();
        return
            std::bit_cast<T>(
                static_cast<std::make_unsigned_t<T>>(
                    std::bit_cast<std::make_unsigned_t<T>>(x) / std::bit_cast<std::make_unsigned_t<T>>(y)));
    }

    bool operator()(bool x, bool y) const {
        if (y == false)
            throw OpException();
        return x;
    }
};

} // namespace ops
