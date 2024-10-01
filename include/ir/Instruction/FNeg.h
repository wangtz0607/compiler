#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/UnaryFloatingArithmeticOperator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class FNeg final : public UnaryFloatingArithmeticOperator {
public:
    explicit FNeg(std::shared_ptr<Value> value) : UnaryFloatingArithmeticOperator(std::move(value)) {}

    std::unique_ptr<Constant> fold() const override;

    void accept(InstructionVisitor &visitor) override {
        visitor.visitFNeg(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitFNeg(*this);
    }

    std::string format() const override {
        return std::format("{:o} = fneg {} {:o}", *this, *value()->type(), *value());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<FNeg>(share(*value()));
    }
};

} // namespace ir
