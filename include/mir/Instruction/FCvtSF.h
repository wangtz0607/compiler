#pragma once

#include <format>
#include <memory>
#include <unordered_set>
#include <utility>

#include "common/Precision.h"
#include "mir/Formatting.h"
#include "mir/Instruction.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class FCvtSF : public Instruction {
public:
    FCvtSF(int dstWidth, Precision srcPrecision, std::shared_ptr<Register> dst, std::shared_ptr<Register> src)
        : dstWidth_(dstWidth),
          srcPrecision_(srcPrecision),
          dst_(RegisterKind::kInteger, std::move(dst)),
          src_(RegisterKind::kFloating, std::move(src)) {}

    int dstWidth() const {
        return dstWidth_;
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
        return std::format("FCVTSF<{}, {}> {}, {}", dstWidth(), specifier(srcPrecision()), *dst(), *src());
    }

    std::unique_ptr<Instruction> clone() const override {
        return std::make_unique<FCvtSF>(dstWidth(), srcPrecision(), share(*dst()), share(*src()));
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFCvtSF(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFCvtSF(*this);
    }

private:
    int dstWidth_;
    Precision srcPrecision_;
    RegisterOperand dst_, src_;
};

} // namespace mir
