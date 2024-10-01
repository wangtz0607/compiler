#include "opt/mir/FunctionTransform.h"

#include "mir/Function.h"
#include "mir/Module.h"

using namespace mir;

bool FunctionTransform::runOnModule(Module &M) {
    bool changed = false;
    for (Function &F : M.functions) {
        if (!F.empty()) {
            changed |= runOnFunction(F);
        }
    }
    return changed;
}
