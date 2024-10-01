#include "opt/ir/passes/BasicBlockMerging.h"

#include <memory>
#include <utility>
#include <vector>

#include "ir/BasicBlock.h"
#include "ir/Function.h"
#include "ir/Instruction.h"
#include "ir/Instruction/Br.h"
#include "ir/Instruction/Phi.h"
#include "ir/Value.h"
#include "utils/Memory.h"

using namespace ir;

namespace {

bool canMergeWithSuccessor(const BasicBlock &B) {
    if (B.empty()) {
        return false;
    }
    if (!dynamic_cast<const Br *>(&B.back())) {
        return false;
    }
    const BasicBlock &succ = *static_cast<const Br *>(&B.back())->dest();
    if (!hasNPredecessors(succ, 1)) {
        return false;
    }
    for (const Instruction &I : succ) {
        if (dynamic_cast<const Phi *>(&I)) {
            return false;
        }
    }
    return true;
}

} // namespace

bool BasicBlockMerging::runOnFunction(Function &F) {
    bool changed = false;

    std::vector<BasicBlock *> merge;

    for (BasicBlock &B : F) {
        if (!hasNPredecessors(B, 1)) {
            merge.push_back(&B);
        }
    }

    for (BasicBlock *B : merge) {
        while (canMergeWithSuccessor(*B)) {
            BasicBlock *succ = &*static_cast<Br *>(&B->back())->dest();
            removeFromParent(B->back());
            std::vector<std::shared_ptr<Instruction>> taken;
            for (Instruction &I : *succ) {
                taken.push_back(share(I));
            }
            for (auto &I : taken) {
                removeFromParent(*I);
            }
            for (auto &I : taken) {
                B->append(std::move(I));
            }
            replaceAllUsesWith(*succ, weaken(*B));
            changed = true;
        }
    }

    std::vector<const BasicBlock *> remove;

    for (const BasicBlock &B : F) {
        if (B.empty()) {
            remove.push_back(&B);
        }
    }

    for (const BasicBlock *B : remove) {
        removeFromParent(*B);
        changed = true;
    }

    return changed;
}
