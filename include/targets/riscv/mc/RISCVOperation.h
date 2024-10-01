#pragma once

#include <utility>

namespace mc {

enum RISCVOperation {
#define OPS
#define X(opcode, mnemonic, enumerator) RISCV_##enumerator = opcode,
#include "targets/riscv/target.def"
#undef X
#undef OPS
};

constexpr const char *mnemonic(RISCVOperation op) {
    switch (op) {
#define OPS
#define X(opcode, mnemonic, enumerator) case RISCV_##enumerator: return mnemonic;
#include "targets/riscv/target.def"
#undef X
#undef OPS
    default:
        std::unreachable();
    }
}

} // namespace mc
