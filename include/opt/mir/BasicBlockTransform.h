#pragma once

#include "mir/BasicBlock.h"
#include "mir/Function.h"
#include "opt/mir/FunctionTransform.h"

namespace mir {

class BasicBlockTransform : public FunctionTransform {
public:
    virtual bool runOnBasicBlock(BasicBlock &B) = 0;
    bool runOnFunction(Function &F) override;
};

} // namespace mir
