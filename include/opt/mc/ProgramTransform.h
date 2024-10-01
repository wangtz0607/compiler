#pragma once

#include "mc/Program.h"

namespace mc {

class ProgramTransform {
public:
    ~ProgramTransform() = default;
    virtual bool runOnProgram(Program &program) = 0;
};

} // namespace mc
