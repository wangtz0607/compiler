#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "common/Precision.h"
#include "mir/Condition.h"
#include "mir/Formatting.h"
#include "mir/Instruction.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class FCmpSet : public Instruction {
public:
    FCmpSet(int dstWidth,
            Precision srcPrecision,
            Condition cond,
            std::shared_ptr<Register> dst,
            std::shared_ptr<Register> src1,
            std::shared_ptr<Register> src2)
        : dstWidth_(dstWidth),
          srcPrecision_(srcPrecision),
          cond_(cond),
          dst_(RegisterKind::kInteger, std::move(dst)),
          src1_(RegisterKind::kFloating, std::move(src1)),
          src2_(RegisterKind::kFloating, std::move(src2)) {}

    int dstWidth() const {
        return dstWidth_;
    }

    Precision srcPrecision() const {
        return srcPrecision_;
    }

    Condition cond() const {
        return cond_;
    }

    void setCond(Condition cond) {
        cond_ = cond;
    }

    template <typename Self>
    auto &dst(this Self &&self) {
        return self.dst_;
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
        return {&dst(), &src1(), &src2()};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {&dst()};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {&src1(), &src2()};
    }

    bool hasSideEffects() const override {
        return true;
    }

    std::string format() const override {
        return std::format(
            "FCMPSET<{}, {}> {}, {}, {}, {}",
            dstWidth(), specifier(srcPrecision()), specifier(cond()), *dst(), *src1(), *src2());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<FCmpSet>(
            dstWidth(), srcPrecision(), cond(), share(*dst()), share(*src1()), share(*src2()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFCmpSet(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFCmpSet(*this);
    }

private:
    int dstWidth_;
    Precision srcPrecision_;
    Condition cond_;
    RegisterOperand dst_, src1_, src2_;
};

} // namespace mir
