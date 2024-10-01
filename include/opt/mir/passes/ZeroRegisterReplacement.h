#pragma once

#include "mir/BasicBlock.h"
#include "mir/PhysicalRegister.h"
#include "opt/mir/BasicBlockTransform.h"

namespace mir {

class ZeroRegisterReplacement final : public BasicBlockTransform {
public:
    explicit ZeroRegisterReplacement(PhysicalRegister *zeroReg) : zeroReg_(zeroReg) {}

    bool runOnBasicBlock(BasicBlock &B) override;

private:
    PhysicalRegister *zeroReg_;
};

} // namespace mir
