#pragma once

#include <memory>
#include <utility>

#include "mini-llvm/common/ExtensionMode.h"
#include "mini-llvm/mir/Immediate.h"
#include "mini-llvm/mir/Instruction.h"
#include "mini-llvm/mir/Instruction/BinaryOperatorI.h"
#include "mini-llvm/mir/InstructionVisitor.h"
#include "mini-llvm/mir/Register.h"
#include "mini-llvm/utils/Memory.h"

namespace mini_llvm::mir {

class SHRAI : public BinaryOperatorI {
public:
    SHRAI(int width,
          std::shared_ptr<Register> dst,
          std::shared_ptr<Register> src1,
          std::unique_ptr<Immediate> src2,
          ExtensionMode extensionMode = ExtensionMode::kNo)
        : BinaryOperatorI(width, std::move(dst), std::move(src1), std::move(src2), extensionMode) {}

    bool hasSideEffects() const override {
        return false;
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<SHRAI>(
            width(), share(*dst()), share(*src1()), src2()->clone(), extensionMode());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitSHRAI(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitSHRAI(*this);
    }

protected:
    const char *mnemonic() const override {
        return "SHRAI";
    }
};

} // namespace mini_llvm::mir
