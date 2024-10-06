#pragma once

namespace mini_llvm::ops {

struct Xor {
    template <typename T>
    T operator()(T x, T y) const {
        return x ^ y;
    }

    bool operator()(bool x, bool y) const {
        return x != y;
    }
};

} // namespace mini_llvm::ops
