#include "opt/ir/passes/JumpThreading.h"

#include <vector>

#include "ir/BasicBlock.h"
#include "ir/Function.h"
#include "ir/Instruction.h"
#include "ir/Instruction/Br.h"
#include "ir/Instruction/Phi.h"
#include "utils/Memory.h"

using namespace ir;

bool JumpThreading::runOnFunction(Function &F) {
    bool changed = false;

    bool changed2;
    do {
        changed2 = false;

        for (BasicBlock &B : F) {
            if (B.size() == 1) {
                if (auto *br = dynamic_cast<Br *>(&B.back())) {
                    BasicBlock *succ = &*br->dest();
                    if (succ != &B) {
                        std::vector<UseBase *> replace;
                        for (BasicBlock *pred : predecessors(B)) {
                            if (!hasPredecessor(*succ, *pred)) {
                                for (Instruction &I : *succ) {
                                    if (auto *phi = dynamic_cast<Phi *>(&I)) {
                                        phi->putIncoming(*pred, share(*getIncomingValue(*phi, B)));
                                        changed2 = true;
                                    }
                                }
                                for (UseBase *use : pred->back().operands()) {
                                    if (&**use == &B) {
                                        replace.push_back(use);
                                    }
                                }
                            }
                        }
                        for (UseBase *use : replace) {
                            use->set(weaken(*succ));
                            changed2 = true;
                        }
                    }
                }
            }
        }

        changed |= changed2;
    } while (changed2);

    return changed;
}
