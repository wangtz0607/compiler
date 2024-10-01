#pragma once

namespace ops {

struct Xor {
    template <typename T>
    T operator()(T x, T y) const {
        return x ^ y;
    }

    bool operator()(bool x, bool y) const {
        return x != y;
    }
};

} // namespace ops
