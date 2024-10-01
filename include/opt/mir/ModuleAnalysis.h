#pragma once

#include "mir/Module.h"

namespace mir {

class ModuleAnalysis {
public:
    virtual ~ModuleAnalysis() = default;
    virtual void runOnModule(const Module &M) = 0;
};

} // namespace mir
