#pragma once

#include "mir/BasicBlock.h"
#include "opt/mir/BasicBlockTransform.h"

namespace mir {

class IdentityMoveElimination final : public BasicBlockTransform {
public:
    bool runOnBasicBlock(BasicBlock &B) override;
};

} // namespace mir
