#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/FloatingToIntegerCastingOperator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Type/IntegerType.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class FPToSI final : public FloatingToIntegerCastingOperator {
public:
    FPToSI(std::shared_ptr<Value> value, std::unique_ptr<IntegerType> type)
        : FloatingToIntegerCastingOperator(std::move(value), std::move(type)) {}

    std::unique_ptr<Constant> fold() const override;

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFPToSI(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFPToSI(*this);
    }

    std::string format() const override {
        return std::format("{:o} = fptosi {} {:o} to {}", *this, *value()->type(), *value(), *type());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<FPToSI>(share(*value()), cast<IntegerType>(type()));
    }
};

} // namespace ir
