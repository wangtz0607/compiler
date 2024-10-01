#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "mir/Immediate.h"
#include "mir/ImmediateOperand.h"
#include "mir/Instruction.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class LI : public Instruction {
public:
    LI(int width, std::shared_ptr<Register> dst, std::unique_ptr<Immediate> src)
        : width_(width), dst_(RegisterKind::kInteger, std::move(dst)), src_(std::move(src)) {}

    int width() const {
        return width_;
    }

    template <typename Self>
    auto &dst(this Self &&self) {
        return self.dst_;
    }

    template <typename Self>
    auto &src(this Self &&self) {
        return self.src_;
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

    std::string format() const override {
        return std::format("LI<{}> {}, {}", width(), *dst(), *src());
    }

    bool hasSideEffects() const override {
        return false;
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<LI>(width(), share(*dst()), src()->clone());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitLI(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitLI(*this);
    }

private:
    int width_;
    RegisterOperand dst_;
    ImmediateOperand src_;
};

} // namespace mir
