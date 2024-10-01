#pragma once

#include <unordered_set>

#include "mir/BasicBlockOperand.h"
#include "mir/Instruction.h"

namespace mir {

class Terminator : public Instruction {
public:
    bool hasSideEffects() const override {
        return true;
    }

    virtual std::unordered_set<const BasicBlockOperand *> successors() const = 0;
    std::unordered_set<BasicBlockOperand *> successors();
};

} // namespace mir
