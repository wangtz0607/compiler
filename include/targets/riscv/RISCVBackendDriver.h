#pragma once

#include "codegen/RegisterAllocator.h"
#include "ir/Module.h"
#include "mc/Program.h"

class RISCVBackendDriver {
public:
    void setRegisterAllocator(RegisterAllocator *registerAllocator) {
        registerAllocator_ = registerAllocator;
    }

    mc::Program run(const ir::Module &IM);

private:
    RegisterAllocator *registerAllocator_{};
};
