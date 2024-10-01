#include "targets/riscv/mir/Instruction/RISCVCall.h"

#include <ranges>
#include <unordered_set>

#include "mir/PhysicalRegister.h"
#include "targets/riscv/mir/RISCVRegister.h"

using namespace mir;
using namespace mir::riscv;

std::unordered_set<PhysicalRegister *> RISCVCall::implicitDsts() const {
    std::unordered_set<PhysicalRegister *> implicitDsts;
    for (PhysicalRegister *physReg : riscvRegs()) {
        if (physReg->isVolatile()) {
            implicitDsts.insert(physReg);
        }
    }
    return implicitDsts;
}

std::unordered_set<PhysicalRegister *> RISCVCall::implicitSrcs() const {
    std::unordered_set<PhysicalRegister *> implicitSrcs{ra(), sp(), gp(), tp(), fp()};
    for (PhysicalRegister *physReg : std::views::take(riscvIntegerArgRegs(), numIntegerArgs())) {
        implicitSrcs.insert(physReg);
    }
    for (PhysicalRegister *physReg : std::views::take(riscvFloatingArgRegs(), numFloatingArgs())) {
        implicitSrcs.insert(physReg);
    }
    return implicitSrcs;
}
