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

class ZExt final : public IntegerCastingOperator {
public:
    ZExt(std::shared_ptr<Value> value, std::unique_ptr<IntegerType> type)
        : IntegerCastingOperator(std::move(value), std::move(type)) {}

    void accept(InstructionVisitor &visitor) override {
        visitor.visitZExt(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitZExt(*this);
    }

    std::unique_ptr<Constant> fold() const override;

    std::string format() const override {
        return std::format("{:o} = zext {} {:o} to {}", *this, *value()->type(), *value(), *type());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<ZExt>(share(*value()), cast<IntegerType>(type()));
    }
};

} // namespace ir
