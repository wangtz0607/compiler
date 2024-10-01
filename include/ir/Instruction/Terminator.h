#pragma once

#include <unordered_set>

#include "ir/BasicBlock.h"
#include "ir/Instruction.h"

namespace ir {

class Terminator : public Instruction {
public:
    virtual std::unordered_set<BasicBlock *> successors() const = 0;
};

} // namespace ir
