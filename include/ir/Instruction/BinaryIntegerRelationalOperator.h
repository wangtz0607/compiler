#pragma once

#include <memory>
#include <utility>

#include "ir/Instruction/BinaryIntegerOperator.h"
#include "ir/Type.h"
#include "ir/Type/I1.h"
#include "ir/Value.h"

namespace ir {

class BinaryIntegerRelationalOperator : public BinaryIntegerOperator {
public:
    std::unique_ptr<Type> type() const override {
        return std::make_unique<I1>();
    }

protected:
    BinaryIntegerRelationalOperator(std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs)
        : BinaryIntegerOperator(std::move(lhs), std::move(rhs)) {}
};

} // namespace ir
