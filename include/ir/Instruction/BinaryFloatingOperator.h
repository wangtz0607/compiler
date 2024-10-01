#pragma once

#include <cassert>
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

class BinaryFloatingOperator : public Operator {
public:
    template <typename Self>
    auto &lhs(this Self &&self) {
        return self.lhs_;
    }

    template <typename Self>
    auto &rhs(this Self &&self) {
        return self.rhs_;
    }

    std::unique_ptr<Type> opType() const {
        assert(*lhs()->type() == *rhs()->type());
        return lhs()->type();
    }

    std::unordered_set<const UseBase *> operands() const override {
        return {&lhs(), &rhs()};
    }

    bool isFoldable() const override {
        return dynamic_cast<const Constant *>(&*lhs()) && dynamic_cast<const Constant *>(&*rhs());
    }

protected:
    BinaryFloatingOperator(std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs)
        : lhs_(this, std::move(lhs)), rhs_(this, std::move(rhs)) {}

private:
    Use<Value, FloatingType> lhs_, rhs_;
};

} // namespace ir
