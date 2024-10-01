#pragma once

#include <memory>
#include <utility>

#include "common/ExtensionMode.h"
#include "mir/Instruction.h"
#include "mir/Instruction/UnaryOperator.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "utils/Memory.h"

namespace mir {

class Mov : public UnaryOperator {
public:
    Mov(int width,
        std::shared_ptr<Register> dst,
        std::shared_ptr<Register> src,
        ExtensionMode extensionMode = ExtensionMode::kNo)
        : UnaryOperator(width, std::move(dst), std::move(src), extensionMode) {}

    bool hasSideEffects() const override {
        return false;
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<Mov>(
            width(), share(*dst()), share(*src()), extensionMode());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitMov(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitMov(*this);
    }

protected:
    const char *mnemonic() const override {
        return "MOV";
    }
};

} // namespace mir
