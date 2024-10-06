#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "mini-llvm/ir/Constant.h"
#include "mini-llvm/ir/Instruction/BinaryIntegerArithmeticOperator.h"
#include "mini-llvm/ir/InstructionVisitor.h"
#include "mini-llvm/ir/Value.h"
#include "mini-llvm/utils/Memory.h"

namespace mini_llvm::ir {

class Add final : public BinaryIntegerArithmeticOperator {
public:
    Add(std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs)
        : BinaryIntegerArithmeticOperator(std::move(lhs), std::move(rhs)) {}

    bool isCommutative() const override {
        return true;
    }

    bool isAssociative() const override {
        return true;
    }

    std::unique_ptr<Constant> fold() const override;

    void accept(InstructionVisitor &visitor) override {
        visitor.visitAdd(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitAdd(*this);
    }

    std::string format() const override {
        return std::format("{:o} = add {} {:o}, {:o}", *this, *opType(), *lhs(), *rhs());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<Add>(share(*lhs()), share(*rhs()));
    }
};

} // namespace mini_llvm::ir
