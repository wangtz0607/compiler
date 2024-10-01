#pragma once

#include <memory>
#include <string>
#include <utility>

#include "mir/Condition.h"
#include "mir/Instruction.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class CondSet : public Instruction {
public:
    CondSet(int width, Condition cond, std::shared_ptr<Register> dst)
        : width_(width), cond_(cond), dst_(RegisterKind::kInteger, std::move(dst)) {}

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
    auto &dst(this Self &&self) {
        return self.dst_;
    }

    std::unordered_set<const RegisterOperand *> regOps() const override {
        return {&dst()};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {&dst()};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {};
    }

    bool hasSideEffects() const override {
        return false;
    }

    std::string format() const override {
        return std::format("CONDSET<{}> {}, {}", width(), specifier(cond()), *dst());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<CondSet>(width(), cond(), share(*dst()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitSet(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitSet(*this);
    }

private:
    int width_;
    Condition cond_;
    RegisterOperand dst_;
};

} // namespace mir
