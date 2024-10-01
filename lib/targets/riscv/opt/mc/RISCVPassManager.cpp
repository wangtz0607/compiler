#include "targets/riscv/opt/mc/RISCVPassManager.h"

#include "mc/Program.h"
#include "opt/mc/passes/RedundantLabelElimination.h"
#include "targets/riscv/opt/mc/passes/RISCVFallthrough.h"

using namespace mc;

void RISCVPassManager::run(Program &program) const {
    RISCVFallthrough          pass1;
    RedundantLabelElimination pass2;

    pass1.runOnProgram(program);
    pass2.runOnProgram(program);
}
