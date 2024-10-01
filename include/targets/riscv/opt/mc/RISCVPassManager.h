#pragma once

#include "mc/Program.h"

namespace mc {

class RISCVPassManager {
public:
    void run(Program &program) const;
};

} // namespace mc
