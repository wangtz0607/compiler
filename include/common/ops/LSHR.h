#pragma once

#include <bit>
#include <climits>
#include <concepts>
#include <type_traits>

#include "common/OpException.h"

namespace ops {

struct LSHR {
    template <typename Tx, typename Ty>
        requires std::integral<Tx> && std::integral<Ty>
    Tx operator()(Tx x, Ty y) const {
        if (y >= static_cast<Ty>(sizeof(Tx) * CHAR_BIT))
            throw OpException();
        return
            std::bit_cast<Tx>(
                static_cast<std::make_unsigned_t<Tx>>(
                    std::bit_cast<std::make_unsigned_t<Tx>>(x) >> y));
    }

    template <typename Ty>
        requires std::integral<Ty>
    bool operator()(bool x, Ty y) const {
        if (y != 0)
            throw OpException();
        return x;
    }
};

} // namespace ops
