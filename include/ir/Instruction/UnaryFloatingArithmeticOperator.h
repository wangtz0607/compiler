#pragma once

#include <memory>
#include <utility>

#include "ir/Instruction/UnaryFloatingOperator.h"
#include "ir/Type.h"
#include "ir/Value.h"

namespace ir {

class UnaryFloatingArithmeticOperator : public UnaryFloatingOperator {
public:
    std::unique_ptr<Type> type() const override {
        return value()->type();
    }

protected:
    explicit UnaryFloatingArithmeticOperator(std::shared_ptr<Value> op)
        : UnaryFloatingOperator(std::move(op)) {}
};

} // namespace ir
