#include "mini-llvm/opt/ir/passes/DeadCodeElimination.h"

#include <queue>
#include <unordered_set>
#include <vector>

#include "mini-llvm/ir/BasicBlock.h"
#include "mini-llvm/ir/Function.h"
#include "mini-llvm/ir/Instruction.h"
#include "mini-llvm/ir/Instruction/Alloca.h"
#include "mini-llvm/ir/Instruction/GetElementPtr.h"
#include "mini-llvm/ir/Instruction/Load.h"
#include "mini-llvm/ir/Instruction/Operator.h"
#include "mini-llvm/ir/Instruction/Phi.h"
#include "mini-llvm/ir/Instruction/Select.h"
#include "mini-llvm/ir/Use.h"

using namespace mini_llvm::ir;

namespace {

bool isCritical(const Instruction &I) {
    return !dynamic_cast<const Operator *>(&I)
        && !dynamic_cast<const GetElementPtr *>(&I)
        && !dynamic_cast<const Select *>(&I)
        && !dynamic_cast<const Alloca *>(&I)
        && !dynamic_cast<const Load *>(&I)
        && !dynamic_cast<const Phi *>(&I);
}

} // namespace

bool DeadCodeElimination::runOnFunction(Function &F) {
    std::unordered_set<const Instruction *> S;
    std::queue<const Instruction *> Q;
    for (const BasicBlock &B : F) {
        for (const Instruction &I : B) {
            if (isCritical(I)) {
                S.insert(&I);
                Q.push(&I);
            }
        }
    }
    while (!Q.empty()) {
        const Instruction *I = Q.front();
        Q.pop();
        for (const UseBase *op : I->operands()) {
            if (auto *II = dynamic_cast<const Instruction *>(&**op)) {
                if (!S.contains(II)) {
                    S.insert(II);
                    Q.push(II);
                }
            }
        }
    }

    std::vector<const Instruction *> remove;
    for (const BasicBlock &B : F) {
        for (const Instruction &I : B) {
            if (!S.contains(&I)) {
                remove.push_back(&I);
            }
        }
    }

    bool changed = false;

    for (const Instruction *I : remove) {
        removeFromParent(*I);
        changed = true;
    }

    return changed;
}
