#pragma once

#include <memory>
#include <utility>

#include "common/ExtensionMode.h"
#include "mir/Instruction.h"
#include "mir/Instruction/BinaryOperator.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "utils/Memory.h"

namespace mir {

class SHL : public BinaryOperator {
public:
    SHL(int width,
        std::shared_ptr<Register> dst,
        std::shared_ptr<Register> src1,
        std::shared_ptr<Register> src2,
        ExtensionMode extensionMode = ExtensionMode::kNo)
        : BinaryOperator(width, std::move(dst), std::move(src1), std::move(src2), extensionMode) {}

    bool hasSideEffects() const override {
        return false;
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<SHL>(
            width(), share(*dst()), share(*src1()), share(*src2()), extensionMode());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitSHL(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitSHL(*this);
    }

protected:
    const char *mnemonic() const override {
        return "SHL";
    }
};

} // namespace mir
