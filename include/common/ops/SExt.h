#pragma once

#include <bit>
#include <concepts>
#include <type_traits>

#include "common/OpException.h"

namespace ops {

template <typename To>
    requires std::integral<To>
struct SExt {
    template <typename From>
        requires std::integral<From>
    To operator()(From) const {
        throw OpException();
    }

    template <typename From>
        requires std::integral<From> && (!std::same_as<From, bool>) && (sizeof(To) >= sizeof(From))
    To operator()(From x) const {
        return std::bit_cast<To>(static_cast<std::make_signed_t<To>>(std::bit_cast<std::make_signed_t<From>>(x)));
    }

    To operator()(bool x) const {
        return std::bit_cast<To>(static_cast<std::make_unsigned_t<To>>(-x));
    }
};

template <>
struct SExt<bool> {
    template <typename From>
        requires std::integral<From>
    bool operator()(From) const {
        throw OpException();
    }

    bool operator()(bool x) const {
        return x;
    }
};

} // namespace ops
