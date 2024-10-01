#pragma once

#include <memory>
#include <unordered_set>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/Operator.h"
#include "ir/Type.h"
#include "ir/Type/FloatingType.h"
#include "ir/Use.h"
#include "ir/Value.h"

namespace ir {

class FloatingCastingOperator : public Operator {
public:
    template <typename Self>
    auto &value(this Self &&self) {
        return self.value_;
    }

    std::unique_ptr<Type> type() const override {
        return type_->clone();
    }

    std::unordered_set<const UseBase *> operands() const override {
        return {&value()};
    }

    bool isFoldable() const override {
        return dynamic_cast<const Constant *>(&*value());
    }

protected:
    FloatingCastingOperator(std::shared_ptr<Value> value, std::unique_ptr<FloatingType> type)
        : value_(this, std::move(value)), type_(std::move(type)) {}

private:
    Use<Value, FloatingType> value_;
    std::unique_ptr<FloatingType> type_;
};

} // namespace ir
