#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "ir/Instruction/BinaryIntegerArithmeticOperator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class LSHR final : public BinaryIntegerArithmeticOperator {
public:
    LSHR(std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs)
        : BinaryIntegerArithmeticOperator(std::move(lhs), std::move(rhs)) {}

    bool isCommutative() const override {
        return false;
    }

    bool isAssociative() const override {
        return false;
    }

    std::unique_ptr<Constant> fold() const override;

    void accept(InstructionVisitor &visitor) override {
        visitor.visitLSHR(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitLSHR(*this);
    }

    std::string format() const override {
        return std::format("{:o} = lshr {} {:o}, {:o}", *this, *opType(), *lhs(), *rhs());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<LSHR>(share(*lhs()), share(*rhs()));
    }
};

} // namespace ir
