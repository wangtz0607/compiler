#pragma once

#include "mir/Function.h"

namespace mir {

class FunctionAnalysis {
public:
    virtual ~FunctionAnalysis() = default;
    virtual void runOnFunction(const Function &F) = 0;
};

} // namespace mir
