#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "common/Precision.h"
#include "mir/Formatting.h"
#include "mir/Instruction.h"
#include "mir/InstructionVisitor.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class FCvt : public Instruction {
public:
    FCvt(Precision dstPrecision,
         Precision srcPrecision,
         std::shared_ptr<Register> dst,
         std::shared_ptr<Register> src)
        : dstPrecision_(dstPrecision),
          srcPrecision_(srcPrecision),
          dst_(RegisterKind::kFloating, std::move(dst)),
          src_(RegisterKind::kFloating, std::move(src)) {}

    Precision dstPrecision() const {
        return dstPrecision_;
    }

    Precision srcPrecision() const {
        return srcPrecision_;
    }

    template <typename Self>
    auto &dst(this Self &&self) {
        return self.dst_;
    }

    template <typename Self>
    auto &src(this Self &&self) {
        return self.src_;
    }

    std::unordered_set<const RegisterOperand *> regOps() const override {
        return {&dst(), &src()};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {&dst()};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {&src()};
    }

    bool hasSideEffects() const override {
        return true;
    }

    std::string format() const override {
        return std::format(
            "FCVT<{}, {}> {}, {}",
            specifier(dstPrecision()), specifier(srcPrecision()), *dst(), *src());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<FCvt>(
            dstPrecision(), srcPrecision(), share(*dst()), share(*src()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFCvt(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFCvt(*this);
    }

private:
    Precision dstPrecision_, srcPrecision_;
    RegisterOperand dst_, src_;
};

} // namespace mir
