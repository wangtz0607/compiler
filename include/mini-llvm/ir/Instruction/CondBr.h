#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "mini-llvm/ir/BasicBlock.h"
#include "mini-llvm/ir/Instruction/Terminator.h"
#include "mini-llvm/ir/InstructionVisitor.h"
#include "mini-llvm/ir/Type.h"
#include "mini-llvm/ir/Type/I1.h"
#include "mini-llvm/ir/Type/Void.h"
#include "mini-llvm/ir/Use.h"
#include "mini-llvm/ir/Value.h"
#include "mini-llvm/utils/Memory.h"

namespace mini_llvm::ir {

class CondBr final : public Terminator {
public:
    CondBr(std::shared_ptr<Value> cond, std::weak_ptr<BasicBlock> trueDest, std::weak_ptr<BasicBlock> falseDest)
        : cond_(this, std::move(cond)), trueDest_(this, std::move(trueDest)), falseDest_(this, std::move(falseDest)) {}

    template <typename Self>
    auto &cond(this Self &&self) {
        return self.cond_;
    }

    template <typename Self>
    auto &trueDest(this Self &&self) {
        return self.trueDest_;
    }

    template <typename Self>
    auto &falseDest(this Self &&self) {
        return self.falseDest_;
    }

    std::unordered_set<BasicBlock *> successors() const override {
        return {&*trueDest(), &*falseDest()};
    }

    std::unordered_set<const UseBase *> operands() const override {
        return {&cond(), &trueDest(), &falseDest()};
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitCondBr(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitCondBr(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<Void>();
    }

    std::string format() const override {
        return std::format(
            "br {} {:o}, {} {:o}, {} {:o}",
            *cond()->type(), *cond(), *trueDest()->type(), *trueDest(), *falseDest()->type(), *falseDest());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<CondBr>(
            share(*cond()), weaken(*trueDest()), weaken(*falseDest()));
    }

private:
    Use<Value, I1> cond_;
    Use<BasicBlock> trueDest_, falseDest_;
};

} // namespace mini_llvm::ir
