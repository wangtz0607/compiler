#include "opt/ir/passes/BranchSimplification.h"

#include <memory>
#include <vector>

#include "ir/BasicBlock.h"
#include "ir/Constant/I1Constant.h"
#include "ir/Function.h"
#include "ir/Instruction.h"
#include "ir/Instruction/Br.h"
#include "ir/Instruction/CondBr.h"
#include "ir/Instruction/Phi.h"
#include "utils/Memory.h"

using namespace ir;

bool BranchSimplification::runOnFunction(Function &F) {
    bool changed = false;

    std::vector<const Instruction *> remove;

    for (const BasicBlock &B : F) {
        if (auto *condBr = dynamic_cast<const CondBr *>(&B.back())) {
            if (auto *cond = dynamic_cast<const I1Constant *>(&*condBr->cond())) {
                BasicBlock *dest, *notDest;
                if (cond->value() == true) {
                    dest = &*condBr->trueDest();
                    notDest = &*condBr->falseDest();
                } else {
                    dest = &*condBr->falseDest();
                    notDest = &*condBr->trueDest();
                }
                addToParent(*condBr, std::make_shared<Br>(weaken(*dest)));
                changed = true;
                remove.push_back(condBr);
                for (Instruction &I : *notDest) {
                    if (auto *phi = dynamic_cast<Phi *>(&I)) {
                        if (hasIncomingBlock(*phi, B)) {
                            removeIncomingBlock(*phi, B);
                            changed = true;
                        }
                    }
                }
                continue;
            }

            if (&*condBr->trueDest() == &*condBr->falseDest()) {
                BasicBlock *dest = &*condBr->trueDest();
                addToParent(*condBr, std::make_shared<Br>(weaken(*dest)));
                changed = true;
                remove.push_back(condBr);
                continue;
            }
        }
    }

    for (const Instruction *I : remove) {
        removeFromParent(*I);
        changed = true;
    }

    return changed;
}
