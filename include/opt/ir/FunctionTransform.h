#pragma once

#include "ir/Function.h"
#include "ir/Module.h"
#include "opt/ir/ModuleTransform.h"

namespace ir {

class FunctionTransform : public ModuleTransform {
public:
    virtual bool runOnFunction(Function &F) = 0;
    bool runOnModule(Module &M) override;
};

} // namespace ir
