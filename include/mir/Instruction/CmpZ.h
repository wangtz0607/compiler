#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "mir/Instruction.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class CmpZ : public Instruction {
public:
    CmpZ(int width, std::shared_ptr<Register> src)
        : width_(width), src_(RegisterKind::kInteger, std::move(src)) {}

    int width() const {
        return width_;
    }

    template <typename Self>
    auto &src(this Self &&self) {
        return self.src_;
    }

    std::unordered_set<const RegisterOperand *> regOps() const override {
        return {&src()};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {&src()};
    }

    bool hasSideEffects() const override {
        return false;
    }

    std::string format() const override {
        return std::format("CMPZ<{}> {}", width(), *src());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<CmpZ>(width(), share(*src()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitCmpZ(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitCmpZ(*this);
    }


private:
    int width_;
    RegisterOperand src_;
};

} // namespace mir
