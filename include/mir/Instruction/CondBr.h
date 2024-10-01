#pragma once

#include <cassert>
#include <format>
#include <memory>
#include <string>
#include <unordered_set>

#include "mir/BasicBlock.h"
#include "mir/BasicBlockOperand.h"
#include "mir/Condition.h"
#include "mir/Instruction.h"
#include "mir/Instruction/Terminator.h"
#include "mir/InstructionVisitor.h"
#include "mir/RegisterOperand.h"

namespace mir {

class CondBr : public Terminator {
public:
    CondBr(Condition cond, BasicBlock *trueDest, BasicBlock *falseDest)
        : cond_(cond), trueDest_(trueDest), falseDest_(falseDest) {}

    Condition cond() const {
        return cond_;
    }

    void setCond(Condition cond) {
        cond_ = cond;
    }

    template <typename Self>
    auto &trueDest(this Self &&self) {
        return self.trueDest_;
    }

    template <typename Self>
    auto &falseDest(this Self &&self) {
        return self.falseDest_;
    }

    std::unordered_set<const BasicBlockOperand *> successors() const override {
        return {&trueDest(), &falseDest()};
    }

    std::unordered_set<const RegisterOperand *> regOps() const override {
        return {};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {};
    }

    std::string format() const override {
        return std::format("CONDBR {}, {:o}, {:o}", specifier(cond()), *trueDest(), *falseDest());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<CondBr>(cond(), &*trueDest(), &*falseDest());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitCondBr(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitCondBr(*this);
    }

private:
    Condition cond_;
    BasicBlockOperand trueDest_, falseDest_;
};

} // namespace mir
