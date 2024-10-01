#pragma once

#include "mir/Module.h"

namespace mir {

class ModuleTransform {
public:
    virtual ~ModuleTransform() = default;
    virtual bool runOnModule(Module &M) = 0;
};

} // namespace mir
