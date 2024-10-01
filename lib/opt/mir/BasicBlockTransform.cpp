#include "opt/mir/BasicBlockTransform.h"

#include "mir/BasicBlock.h"
#include "mir/Function.h"

using namespace mir;

bool BasicBlockTransform::runOnFunction(Function &F) {
    bool changed = false;
    for (BasicBlock &B : F) {
        changed |= runOnBasicBlock(B);
    }
    return changed;
}
