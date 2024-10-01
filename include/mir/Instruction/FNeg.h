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

class FNeg : public FUnaryOperator {
public:
    FNeg(Precision precision, std::shared_ptr<Register> dst, std::shared_ptr<Register> src)
        : FUnaryOperator(precision, std::move(dst), std::move(src)) {}

    bool hasSideEffects() const override {
        return true;
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<FNeg>(precision(), share(*dst()), share(*src()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFNeg(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFNeg(*this);
    }

protected:
    const char *mnemonic() const override {
        return "FNEG";
    }
};

} // namespace mir
