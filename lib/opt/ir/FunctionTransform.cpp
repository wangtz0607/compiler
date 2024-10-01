#include "opt/ir/FunctionTransform.h"

#include "ir/Function.h"
#include "ir/Module.h"

using namespace ir;

bool FunctionTransform::runOnModule(Module &M) {
    bool changed = false;
    for (Function &F : M.functions) {
        if (!F.empty()) {
            changed |= runOnFunction(F);
        }
    }
    return changed;
}
