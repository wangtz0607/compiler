#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/IntegerToFloatingCastingOperator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Type/FloatingType.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class SIToFP final : public IntegerToFloatingCastingOperator {
public:
    SIToFP(std::shared_ptr<Value> value, std::unique_ptr<FloatingType> type)
        : IntegerToFloatingCastingOperator(std::move(value), std::move(type)) {}

    std::unique_ptr<Constant> fold() const override;

    void accept(InstructionVisitor &visitor) override {
        visitor.visitSIToFP(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitSIToFP(*this);
    }

    std::string format() const override {
        return std::format("{:o} = sitofp {} {:o} to {}", *this, *value()->type(), *value(), *type());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<SIToFP>(share(*value()), cast<FloatingType>(type()));
    }
};

} // namespace ir
