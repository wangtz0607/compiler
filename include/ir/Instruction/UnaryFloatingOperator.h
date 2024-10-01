#pragma once

#include <memory>
#include <unordered_set>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/Operator.h"
#include "ir/Type/FloatingType.h"
#include "ir/Use.h"
#include "ir/Value.h"

namespace ir {

class UnaryFloatingOperator : public Operator {
public:
    template <typename Self>
    auto &value(this Self &&self) {
        return self.value_;
    }

    std::unordered_set<const UseBase *> operands() const override {
        return {&value()};
    }

    bool isFoldable() const override {
        return dynamic_cast<const Constant *>(&*value());
    }

protected:
    explicit UnaryFloatingOperator(std::shared_ptr<Value> value) : value_(this, std::move(value)) {}

private:
    Use<Value, FloatingType> value_;
};

} // namespace ir
