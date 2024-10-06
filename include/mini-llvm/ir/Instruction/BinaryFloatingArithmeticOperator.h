#pragma once

#include <memory>
#include <utility>

#include "mini-llvm/ir/Instruction/BinaryFloatingOperator.h"
#include "mini-llvm/ir/Type.h"
#include "mini-llvm/ir/Value.h"

namespace mini_llvm::ir {

class BinaryFloatingArithmeticOperator : public BinaryFloatingOperator {
public:
    std::unique_ptr<Type> type() const override {
        return opType();
    }

    // x op y == y op x
    virtual bool isCommutative() const = 0;

protected:
    BinaryFloatingArithmeticOperator(std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs)
        : BinaryFloatingOperator(std::move(lhs), std::move(rhs)) {}
};

} // namespace mini_llvm::ir
