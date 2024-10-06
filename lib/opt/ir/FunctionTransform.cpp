#include "mini-llvm/opt/ir/FunctionTransform.h"

#include "mini-llvm/ir/Function.h"
#include "mini-llvm/ir/Module.h"

using namespace mini_llvm::ir;

bool FunctionTransform::runOnModule(Module &M) {
    bool changed = false;
    for (Function &F : M.functions) {
        if (!F.empty()) {
            changed |= runOnFunction(F);
        }
    }
    return changed;
}
