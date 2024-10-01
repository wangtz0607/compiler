#pragma once

#include <concepts>
#include <memory>
#include <utility>

#include "mir/BasicBlock.h"
#include "mir/Instruction.h"

namespace mir {

class BasicBlockBuilder {
public:
    BasicBlockBuilder() = default;

    BasicBlockBuilder(BasicBlock *block, BasicBlock::const_iterator pos)
        : block_(block), pos_(pos) {}

    explicit BasicBlockBuilder(BasicBlock *block)
        : block_(block), pos_(block->end()) {}

    void setPos(BasicBlock *block, BasicBlock::const_iterator pos) {
        block_ = block;
        pos_ = pos;
    }

    void setPos(BasicBlock *block) {
        setPos(block, block->end());
    }

    template <typename T>
        requires std::derived_from<T, Instruction>
    T &add(std::unique_ptr<T> I) const {
        return block_->add(pos_, std::move(I));
    }

private:
    BasicBlock *block_{};
    BasicBlock::const_iterator pos_{};
};

} // namespace mir
