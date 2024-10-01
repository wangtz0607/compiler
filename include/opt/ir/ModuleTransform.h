#pragma once

#include "ir/Module.h"

namespace ir {

class ModuleTransform {
public:
    virtual ~ModuleTransform() = default;
    virtual bool runOnModule(Module &M) = 0;
};

} // namespace ir
