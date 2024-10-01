#pragma once

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

class FStore : public Instruction {
public:
    FStore(Precision precision, MemoryOperand dst, std::shared_ptr<Register> src)
        : precision_(precision), dst_(std::move(dst)), src_(RegisterKind::kFloating, std::move(src)) {}

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
        return {&dst().baseReg(), &src()};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {&dst().baseReg(), &src()};
    }

    bool hasSideEffects() const override {
        return true;
    }

    std::string format() const override {
        return std::format("FSTORE<{}> {}, {}", specifier(precision()), dst(), *src());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<FStore>(precision(), dst().clone(), share(*src()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFStore(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFStore(*this);
    }

private:
    Precision precision_;
    MemoryOperand dst_;
    RegisterOperand src_;
};

} // namespace mir
