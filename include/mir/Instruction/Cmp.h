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

class Cmp : public Instruction {
public:
    Cmp(int width, std::shared_ptr<Register> src1, std::shared_ptr<Register> src2)
        : width_(width),
          src1_(RegisterKind::kInteger, std::move(src1)),
          src2_(RegisterKind::kInteger, std::move(src2)) {}

    int width() const {
        return width_;
    }

    template <typename Self>
    auto &src1(this Self &&self) {
        return self.src1_;
    }

    template <typename Self>
    auto &src2(this Self &&self) {
        return self.src2_;
    }

    std::unordered_set<const RegisterOperand *> regOps() const override {
        return {&src1(), &src2()};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {&src1(), &src2()};
    }

    bool hasSideEffects() const override {
        return false;
    }

    std::string format() const override {
        return std::format("CMP<{}> {}, {}", width(), *src1(), *src2());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<Cmp>(width(), share(*src1()), share(*src2()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitCmp(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitCmp(*this);
    }

private:
    int width_;
    RegisterOperand src1_, src2_;
};

} // namespace mir
