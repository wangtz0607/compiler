#pragma once

#include "ir/Module.h"

namespace ir {

class ModuleAnalysis {
public:
    virtual ~ModuleAnalysis() = default;
    virtual void runOnModule(const Module &M) = 0;
};

} // namespace ir
