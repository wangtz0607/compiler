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

class SHLI : public BinaryOperatorI {
public:
    SHLI(int width,
         std::shared_ptr<Register> dst,
         std::shared_ptr<Register> src1,
         std::unique_ptr<Immediate> src2,
         ExtensionMode extensionMode = ExtensionMode::kNo)
        : BinaryOperatorI(width, std::move(dst), std::move(src1), std::move(src2), extensionMode) {}

    bool hasSideEffects() const override {
        return false;
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<SHLI>(
            width(), share(*dst()), share(*src1()), src2()->clone(), extensionMode());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitSHLI(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitSHLI(*this);
    }

protected:
    const char *mnemonic() const override {
        return "SHLI";
    }
};

} // namespace mir
