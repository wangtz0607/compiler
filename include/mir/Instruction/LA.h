#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "mir/GlobalVarOperand.h"
#include "mir/Instruction.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class LA : public Instruction {
public:
    LA(int width, std::shared_ptr<Register> dst, GlobalVar *src)
        : width_(width), dst_(RegisterKind::kInteger, std::move(dst)), src_(src) {}

    int width() const {
        return width_;
    }

    template <typename Self>
    auto &dst(this Self &&self) {
        return self.dst_;
    }

    template <typename Self>
    auto &src(this Self &&self) {
        return self.src_;
    }

    std::unordered_set<const mir::RegisterOperand *> regOps() const override {
        return {&dst()};
    }

    std::unordered_set<const mir::RegisterOperand *> dsts() const override {
        return {&dst()};
    }

    std::unordered_set<const mir::RegisterOperand *> srcs() const override {
        return {};
    }

    bool hasSideEffects() const override {
        return false;
    }

    std::string format() const override {
        return std::format("LA<{}> {}, {:o}", width(), *dst(), *src());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<LA>(width(), share(*dst()), &*src());
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitLA(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitLA(*this);
    }

private:
    int width_;
    RegisterOperand dst_;
    GlobalVarOperand src_;
};

} // namespace mir
