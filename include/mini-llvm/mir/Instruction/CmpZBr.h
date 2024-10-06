#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "mini-llvm/mir/BasicBlock.h"
#include "mini-llvm/mir/BasicBlockOperand.h"
#include "mini-llvm/mir/Condition.h"
#include "mini-llvm/mir/Instruction/Terminator.h"
#include "mini-llvm/mir/InstructionVisitor.h"
#include "mini-llvm/mir/Register.h"
#include "mini-llvm/mir/RegisterKind.h"
#include "mini-llvm/mir/RegisterOperand.h"
#include "mini-llvm/utils/Memory.h"

namespace mini_llvm::mir {

class CmpZBr : public Terminator {
public:
    CmpZBr(int width,
           Condition cond,
           std::shared_ptr<Register> src,
           BasicBlock *trueDest,
           BasicBlock *falseDest)
        : width_(width),
          cond_(cond),
          src_(RegisterKind::kInteger, std::move(src)),
          trueDest_(trueDest),
          falseDest_(falseDest) {}

    int width() const {
        return width_;
    }

    Condition cond() const {
        return cond_;
    }

    void setCond(Condition cond) {
        cond_ = cond;
    }

    template <typename Self>
    auto &src(this Self &&self) {
        return self.src_;
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
        return {&src()};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {&src()};
    }

    std::string format() const override {
        return std::format(
            "CMPZBR<{}> {}, {}, {:o}, {:o}",
            width(), specifier(cond()), *src(), *trueDest(), *falseDest());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<CmpZBr>(
            width(), cond(), share(*src()), &*trueDest(), &*falseDest());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitCmpZBr(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitCmpZBr(*this);
    }

private:
    int width_;
    Condition cond_;
    RegisterOperand src_;
    BasicBlockOperand trueDest_, falseDest_;
};

} // namespace mini_llvm::mir
