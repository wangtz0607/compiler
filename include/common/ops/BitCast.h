#pragma once

#include <bit>
#include <concepts>

#include "common/OpException.h"

namespace ops {

template <typename To>
struct BitCast {
    template <typename From>
    To operator()(From) const {
        throw OpException();
    }

    template <typename From>
        requires (!std::same_as<From, bool>) && (sizeof(To) == sizeof(From))
    To operator()(From x) const {
        return std::bit_cast<To>(x);
    }
};

template <>
struct BitCast<bool> {
    template <typename From>
    bool operator()(From) const {
        throw OpException();
    }

    bool operator()(bool x) const {
        return x;
    }
};

} // namespace ops
