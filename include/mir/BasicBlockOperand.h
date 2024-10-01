#pragma once

#include "mir/BasicBlock.h"

namespace mir {

class BasicBlockOperand {
public:
    explicit BasicBlockOperand(BasicBlock *block) : block_(block) {}

    BasicBlock &operator*() const {
        return *block_;
    }

    BasicBlock *operator->() const {
        return block_;
    }

    void set(BasicBlock *block) {
        block_ = block;
    }

private:
    BasicBlock *block_;
};

} // namespace mir
