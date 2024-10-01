#pragma once

#include "mir/Module.h"

namespace mir {

class RISCVPassManager {
public:
    void runBeforeRegisterAllocation(Module &M) const;
    void runAfterRegisterAllocation(Module &M) const;
};

} // namespace mir
