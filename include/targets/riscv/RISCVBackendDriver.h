#pragma once

#include "ir/Module.h"
#include "mc/Program.h"

class RISCVBackendDriver {
public:
    mc::Program run(const ir::Module &IM);
};
