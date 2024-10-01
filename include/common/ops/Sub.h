#pragma once

#include <bit>
#include <concepts>
#include <type_traits>

namespace ops {

struct Sub {
    template <typename T>
        requires std::integral<T>
    T operator()(T x, T y) const {
        return
            std::bit_cast<T>(
                static_cast<std::make_unsigned_t<T>>(
                    std::bit_cast<std::make_unsigned_t<T>>(x) - std::bit_cast<std::make_unsigned_t<T>>(y)));
    }

    bool operator()(bool x, bool y) const {
        return x != y;
    }
};

} // namespace ops
