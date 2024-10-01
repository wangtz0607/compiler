#pragma once

#include "mir/BasicBlock.h"

namespace mir {

class BasicBlockAnalysis {
public:
    virtual ~BasicBlockAnalysis() = default;
    virtual void runOnBasicBlock(const BasicBlock &B) = 0;
};

} // namespace mir
