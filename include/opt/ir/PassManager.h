#pragma once

#include "ir/Module.h"
#include "opt/ir/ModuleTransform.h"

namespace ir {

class PassManager {
public:
    void setVerifyAfterEach(bool verifyAfterEach) {
        verifyAfterEach_ = verifyAfterEach;
    }

    void run(Module &M) const;

private:
    bool verifyAfterEach_ = false;

    bool run(ModuleTransform &pass, Module &M) const;
};

} // namespace ir
