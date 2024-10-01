#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "common/Precision.h"
#include "mir/Formatting.h"
#include "mir/Instruction.h"
#include "mir/InstructionVisitor.h"
#include "mir/MemoryOperand.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class FLoad : public Instruction {
public:
    FLoad(Precision precision, std::shared_ptr<Register> dst, MemoryOperand src)
        : precision_(precision),
          dst_(RegisterKind::kFloating, std::move(dst)),
          src_(std::move(src)) {}

    Precision precision() const {
        return precision_;
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
        return {&dst(), &src().baseReg()};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {&dst()};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {&src().baseReg()};
    }

    bool hasSideEffects() const override {
        return true;
    }

    std::string format() const override {
        return std::format("FLOAD<{}> {}, {}", specifier(precision()), *dst(), src());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<FLoad>(precision(), share(*dst()), src().clone());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFLoad(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFLoad(*this);
    }

private:
    Precision precision_;
    RegisterOperand dst_;
    MemoryOperand src_;
};

} // namespace mir
