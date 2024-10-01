#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "mir/Condition.h"
#include "mir/Instruction.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class CmpSet : public Instruction {
public:
    CmpSet(int dstWidth,
           int srcWidth,
           Condition cond,
           std::shared_ptr<Register> dst,
           std::shared_ptr<Register> src1,
           std::shared_ptr<Register> src2)
        : dstWidth_(dstWidth),
          srcWidth_(srcWidth),
          cond_(cond),
          dst_(RegisterKind::kInteger, std::move(dst)),
          src1_(RegisterKind::kInteger, std::move(src1)),
          src2_(RegisterKind::kInteger, std::move(src2)) {}

    int dstWidth() const {
        return dstWidth_;
    }

    int srcWidth() const {
        return srcWidth_;
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
        return false;
    }

    std::string format() const override {
        return std::format(
            "CMPSET<{}, {}> {}, {}, {}, {}",
            dstWidth(), srcWidth(), specifier(cond()), *dst(), *src1(), *src2());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<CmpSet>(
            dstWidth(), srcWidth(), cond(), share(*dst()), share(*src1()), share(*src2()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitCmpSet(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitCmpSet(*this);
    }

private:
    int dstWidth_, srcWidth_;
    Condition cond_;
    RegisterOperand dst_, src1_, src2_;
};

} // namespace mir
