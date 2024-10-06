#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "mini-llvm/ir/BasicBlock.h"
#include "mini-llvm/ir/Instruction/Terminator.h"
#include "mini-llvm/ir/InstructionVisitor.h"
#include "mini-llvm/ir/Type.h"
#include "mini-llvm/ir/Type/Void.h"
#include "mini-llvm/ir/Use.h"
#include "mini-llvm/ir/Value.h"
#include "mini-llvm/utils/Memory.h"

namespace mini_llvm::ir {

class Br final : public Terminator {
public:
    explicit Br(std::weak_ptr<BasicBlock> dest) : dest_(this, std::move(dest)) {}

    template <typename Self>
    auto &dest(this Self &&self) {
        return self.dest_;
    }

    std::unordered_set<BasicBlock *> successors() const override {
        return {&*dest()};
    }

    std::unordered_set<const UseBase *> operands() const override {
        return {&dest()};
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitBr(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitBr(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<Void>();
    }

    std::string format() const override {
        return std::format("br {} {:o}", *dest()->type(), *dest());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<Br>(weaken(*dest()));
    }

private:
    Use<BasicBlock> dest_;
};

} // namespace mini_llvm::ir
