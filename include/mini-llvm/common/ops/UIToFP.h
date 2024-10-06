#pragma once

#include <bit>
#include <concepts>
#include <type_traits>

namespace mini_llvm::ops {

template <typename To>
    requires std::floating_point<To>
struct UIToFP {
    template <typename From>
        requires std::integral<From>
    To operator()(From x) const {
        return static_cast<To>(std::bit_cast<std::make_unsigned_t<From>>(x));
    }

    To operator()(bool x) const {
        return static_cast<To>(x);
    }
};

} // namespace mini_llvm::ops
