#pragma once

#include <memory>
#include <unordered_set>
#include <utility>

#include "mini-llvm/ir/Constant.h"
#include "mini-llvm/ir/Instruction/Operator.h"
#include "mini-llvm/ir/Type.h"
#include "mini-llvm/ir/Type/FloatingType.h"
#include "mini-llvm/ir/Type/IntegerType.h"
#include "mini-llvm/ir/Use.h"
#include "mini-llvm/ir/Value.h"

namespace mini_llvm::ir {

class FloatingToIntegerCastingOperator : public Operator {
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
    FloatingToIntegerCastingOperator(std::shared_ptr<Value> value, std::unique_ptr<IntegerType> type)
        : value_(this, std::move(value)), type_(std::move(type)) {}

private:
    Use<Value, FloatingType> value_;
    std::unique_ptr<IntegerType> type_;
};

} // namespace mini_llvm::ir
