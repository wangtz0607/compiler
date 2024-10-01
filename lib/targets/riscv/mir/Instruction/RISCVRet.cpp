#include "targets/riscv/mir/Instruction/RISCVRet.h"

#include <ranges>
#include <unordered_set>

#include "mir/PhysicalRegister.h"
#include "targets/riscv/mir/RISCVRegister.h"

using namespace mir;
using namespace mir::riscv;

std::unordered_set<PhysicalRegister *> RISCVRet::implicitSrcs() const {
    std::unordered_set<PhysicalRegister *> implicitSrcs{ra(), sp(), gp(), tp(), fp()};
    for (PhysicalRegister *physReg : std::views::take(riscvIntegerResultRegs(), numIntegerResults())) {
        implicitSrcs.insert(physReg);
    }
    for (PhysicalRegister *physReg : std::views::take(riscvFloatingResultRegs(), numFloatingResults())) {
        implicitSrcs.insert(physReg);
    }
    return implicitSrcs;
}
