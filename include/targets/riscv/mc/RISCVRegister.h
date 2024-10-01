#pragma once

#include <utility>

namespace mc {

enum RISCVRegister {
#define REGS
#define X(idx, name, kind, isVolatile, isAllocatable) RISCV_##name = idx,
#include "targets/riscv/target.def"
#undef X
#undef REGS
};

constexpr const char *name(RISCVRegister reg) {
    switch (reg) {
#define REGS
#define X(idx, name, kind, isVolatile, isAllocatable) case RISCV_##name: return #name;
#include "targets/riscv/target.def"
#undef X
#undef REGS
    default:
        std::unreachable();
    }
}

} // namespace mc
