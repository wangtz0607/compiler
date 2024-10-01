#pragma once

#include <bit>
#include <concepts>
#include <type_traits>

namespace ops {

struct SLT {
    template <typename T>
        requires std::integral<T>
    bool operator()(T x, T y) const {
        return std::bit_cast<std::make_signed_t<T>>(x) < std::bit_cast<std::make_signed_t<T>>(y);
    }

    bool operator()(bool x, bool y) const {
        return x && !y;
    }
};

} // namespace ops
