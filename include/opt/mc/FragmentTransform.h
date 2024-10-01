#pragma once

#include "mc/Fragment.h"
#include "mc/Program.h"
#include "opt/mc/ProgramTransform.h"

namespace mc {

class FragmentTransform : public ProgramTransform {
public:
    virtual bool runOnFragment(Fragment &fragment) = 0;
    bool runOnProgram(Program &program) override;
};

} // namespace mc
