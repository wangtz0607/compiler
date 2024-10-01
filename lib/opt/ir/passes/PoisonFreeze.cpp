#include "opt/ir/passes/PoisonFreeze.h"

#include "ir/BasicBlock.h"
#include "ir/Constant/PoisonValue.h"
#include "ir/Function.h"
#include "ir/Instruction.h"
#include "ir/Use.h"

using namespace ir;

bool PoisonFreeze::runOnFunction(Function &F) {
    bool changed = false;

    for (BasicBlock &B : F) {
        for (Instruction &I : B) {
            for (UseBase *op : I.operands()) {
                if (dynamic_cast<const PoisonValue *>(&**op)) {
                    op->set((*op)->type()->zeroValue());
                    changed = true;
                }
            }
        }
    }

    return changed;
}
