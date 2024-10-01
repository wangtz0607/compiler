#pragma once

#include <memory>
#include <utility>

#include "common/ExtensionMode.h"
#include "mir/Immediate.h"
#include "mir/Instruction.h"
#include "mir/Instruction/BinaryOperatorI.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "utils/Memory.h"

namespace mir {

class SHRLI : public BinaryOperatorI {
public:
    SHRLI(int width,
          std::shared_ptr<Register> dst,
          std::shared_ptr<Register> src1,
          std::unique_ptr<Immediate> src2,
          ExtensionMode extensionMode = ExtensionMode::kNo)
        : BinaryOperatorI(width, std::move(dst), std::move(src1), std::move(src2), extensionMode) {}

    bool hasSideEffects() const override {
        return false;
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<SHRLI>(
            width(), share(*dst()), share(*src1()), src2()->clone(), extensionMode());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitSHRLI(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitSHRLI(*this);
    }

protected:
    const char *mnemonic() const override {
        return "SHRLI";
    }
};

} // namespace mir
