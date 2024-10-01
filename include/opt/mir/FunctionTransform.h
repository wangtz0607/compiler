#pragma once

#include "mir/Function.h"
#include "mir/Module.h"
#include "opt/mir/ModuleTransform.h"

namespace mir {

class FunctionTransform : public ModuleTransform {
public:
    virtual bool runOnFunction(Function &F) = 0;
    bool runOnModule(Module &M) override;
};

} // namespace mir
