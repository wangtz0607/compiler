#pragma once

#include <memory>
#include <utility>

#include "common/Precision.h"
#include "mir/Instruction.h"
#include "mir/Instruction/FBinaryOperator.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "utils/Memory.h"

namespace mir {

class FDiv : public FBinaryOperator {
public:
    FDiv(Precision precision,
         std::shared_ptr<Register> dst,
         std::shared_ptr<Register> src1,
         std::shared_ptr<Register> src2)
        : FBinaryOperator(precision, std::move(dst), std::move(src1), std::move(src2)) {}

    bool hasSideEffects() const override {
        return true;
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<FDiv>(
            precision(), share(*dst()), share(*src1()), share(*src2()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFDiv(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFDiv(*this);
    }

protected:
    const char *mnemonic() const override {
        return "FDIV";
    }
};

} // namespace mir
