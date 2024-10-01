#pragma once

#include "mir/Function.h"
#include "opt/mir/FunctionTransform.h"

namespace mir {

class DeadCodeElimination : public FunctionTransform {
public:
    bool runOnFunction(Function &F) override;
};

} // namespace mir
