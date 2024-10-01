#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "ir/Instruction/Operator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Type.h"
#include "ir/Use.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class BitCast final : public Operator {
public:
    BitCast(std::shared_ptr<Value> value, std::unique_ptr<Type> type)
        : value_(this, std::move(value)), type_(std::move(type)) {}

    template <typename Self>
    auto &value(this Self &&self) {
        return self.value_;
    }

    std::unordered_set<const UseBase *> operands() const override {
        return {&value()};
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitBitCast(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitBitCast(*this);
    }

    std::unique_ptr<Type> type() const override {
        return type_->clone();
    }

    std::string format() const override {
        return std::format("{:o} = bitcast {} {:o} to {}", *this, *value()->type(), *value(), *type());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<BitCast>(share(*value()), type());
    }

private:
    Use<Value> value_;
    std::unique_ptr<Type> type_;
};

} // namespace ir
