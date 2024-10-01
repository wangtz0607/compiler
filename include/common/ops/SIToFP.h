#pragma once

#include <bit>
#include <concepts>
#include <type_traits>

namespace ops {

template <typename To>
    requires std::floating_point<To>
struct SIToFP {
    template <typename From>
        requires std::integral<From>
    To operator()(From x) const {
        return static_cast<To>(std::bit_cast<std::make_signed_t<From>>(x));
    }

    To operator()(bool x) const {
        return static_cast<To>(x);
    }
};

} // namespace ops
