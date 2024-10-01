#include "opt/ir/PassManager.h"

#include "ir/Module.h"
#include "opt/ir/ModuleTransform.h"
#include "opt/ir/passes/AlgebraicSimplification.h"
#include "opt/ir/passes/BasicBlockMerging.h"
#include "opt/ir/passes/BranchSimplification.h"
#include "opt/ir/passes/ConstantFolding.h"
#include "opt/ir/passes/DeadCodeElimination.h"
#include "opt/ir/passes/FunctionInlining.h"
#include "opt/ir/passes/JumpThreading.h"
#include "opt/ir/passes/Mem2Reg.h"
#include "opt/ir/passes/PoisonFreeze.h"
#include "opt/ir/passes/PoisonPropagation.h"
#include "opt/ir/passes/UnreachableBlockElimination.h"
#include "opt/ir/passes/VerificationAnalysis.h"

using namespace ir;

void PassManager::run(Module &M) const {
    Mem2Reg pass;
    run(pass, M);

    bool changed;
    do {
        changed = false;

        bool changed2;
        do {
            changed2 = false;

            DeadCodeElimination         pass1;
            JumpThreading               pass2;
            UnreachableBlockElimination pass3;
            AlgebraicSimplification     pass4;
            ConstantFolding             pass5;
            PoisonPropagation           pass6;
            BranchSimplification        pass7;
            BasicBlockMerging           pass8;
            FunctionInlining            pass9;

            changed2 |= run(pass1, M);
            changed2 |= run(pass2, M);
            changed2 |= run(pass3, M);
            changed2 |= run(pass4, M);
            changed2 |= run(pass5, M);
            changed2 |= run(pass6, M);
            changed2 |= run(pass7, M);
            changed2 |= run(pass8, M);
            changed2 |= run(pass9, M);

            changed |= changed2;
        } while (changed2);

        PoisonFreeze pass;

        changed |= run(pass, M);
    } while (changed);
}

bool PassManager::run(ModuleTransform &pass, Module &M) const {
    bool changed = pass.runOnModule(M);
    if (verifyAfterEach_) {
        VerificationAnalysis pass2;
        pass2.runOnModule(M);
    }
    return changed;
}
