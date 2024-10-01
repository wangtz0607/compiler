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

class SExt final : public IntegerCastingOperator {
public:
    SExt(std::shared_ptr<Value> value, std::unique_ptr<IntegerType> type)
        : IntegerCastingOperator(std::move(value), std::move(type)) {}

    void accept(InstructionVisitor &visitor) override {
        visitor.visitSExt(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitSExt(*this);
    }

    std::unique_ptr<Constant> fold() const override;

    std::string format() const override {
        return std::format("{:o} = sext {} {:o} to {}", *this, *value()->type(), *value(), *type());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<SExt>(share(*value()), cast<IntegerType>(type()));
    }
};

} // namespace ir
