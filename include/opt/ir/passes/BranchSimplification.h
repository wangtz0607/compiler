#pragma once

#include "ir/Function.h"
#include "opt/ir/FunctionTransform.h"

namespace ir {

class BranchSimplification final : public FunctionTransform {
public:
    bool runOnFunction(Function &F) override;
};

} // namespace ir
