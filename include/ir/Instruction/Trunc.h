#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/IntegerCastingOperator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Type/IntegerType.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class Trunc final : public IntegerCastingOperator {
public:
    Trunc(std::shared_ptr<Value> value, std::unique_ptr<IntegerType> type)
        : IntegerCastingOperator(std::move(value), std::move(type)) {}

    void accept(InstructionVisitor &visitor) override {
        visitor.visitTrunc(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitTrunc(*this);
    }

    std::unique_ptr<Constant> fold() const override;

    std::string format() const override {
        return std::format("{:o} = trunc {} {:o} to {}", *this, *value()->type(), *value(), *type());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<Trunc>(share(*value()), cast<IntegerType>(type()));
    }
};

} // namespace ir
