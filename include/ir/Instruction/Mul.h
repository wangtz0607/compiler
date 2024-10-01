#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/BinaryIntegerArithmeticOperator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class Mul final : public BinaryIntegerArithmeticOperator {
public:
    Mul(std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs)
        : BinaryIntegerArithmeticOperator(std::move(lhs), std::move(rhs)) {}

    bool isCommutative() const override {
        return true;
    }

    bool isAssociative() const override {
        return true;
    }

    std::unique_ptr<Constant> fold() const override;

    void accept(InstructionVisitor &visitor) override {
        visitor.visitMul(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitMul(*this);
    }

    std::string format() const override {
        return std::format("{:o} = mul {} {:o}, {:o}", *this, *opType(), *lhs(), *rhs());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<Mul>(share(*lhs()), share(*rhs()));
    }
};

} // namespace ir
