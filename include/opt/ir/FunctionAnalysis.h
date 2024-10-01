#pragma once

#include "ir/Function.h"

namespace ir {

class FunctionAnalysis {
public:
    virtual ~FunctionAnalysis() = default;
    virtual void runOnFunction(const Function &F) = 0;
};

} // namespace ir
