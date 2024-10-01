#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/BinaryFloatingArithmeticOperator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class FMul final : public BinaryFloatingArithmeticOperator {
public:
    FMul(std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs)
        : BinaryFloatingArithmeticOperator(std::move(lhs), std::move(rhs)) {}

    bool isCommutative() const override {
        return true;
    }

    std::unique_ptr<Constant> fold() const override;

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFMul(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFMul(*this);
    }

    std::string format() const override {
        return std::format("{:o} = fmul {} {:o}, {:o}", *this, *opType(), *lhs(), *rhs());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<FMul>(share(*lhs()), share(*rhs()));
    }
};

} // namespace ir
