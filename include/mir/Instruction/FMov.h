#pragma once

#include <memory>
#include <utility>

#include "common/Precision.h"
#include "mir/Instruction.h"
#include "mir/Instruction/FUnaryOperator.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "utils/Memory.h"

namespace mir {

class FMov : public FUnaryOperator {
public:
    FMov(Precision precision, std::shared_ptr<Register> dst, std::shared_ptr<Register> src)
        : FUnaryOperator(precision, std::move(dst), std::move(src)) {}

    bool hasSideEffects() const override {
        return true;
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<FMov>(precision(), share(*dst()), share(*src()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFMov(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFMov(*this);
    }

protected:
    const char *mnemonic() const override {
        return "FMOV";
    }
};

} // namespace mir
