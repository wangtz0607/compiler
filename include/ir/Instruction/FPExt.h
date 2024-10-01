#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/FloatingCastingOperator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Type/FloatingType.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class FPExt final : public FloatingCastingOperator {
public:
    FPExt(std::shared_ptr<Value> value, std::unique_ptr<FloatingType> type)
        : FloatingCastingOperator(std::move(value), std::move(type)) {}

    std::unique_ptr<Constant> fold() const override;

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFPExt(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFPExt(*this);
    }

    std::string format() const override {
        return std::format("{:o} = fpext {} {:o} to {}", *this, *value()->type(), *value(), *type());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<FPExt>(share(*value()), cast<FloatingType>(type()));
    }
};

} // namespace ir
