#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <typeinfo>

#include "common/ops/SExt.h"
#include "common/ops/ZExt.h"
#include "ir/Constant/IntegerConstant.h"
#include "ir/ConstantVisitor.h"
#include "ir/Type.h"
#include "ir/Type/I32.h"
#include "ir/Value.h"

namespace ir {

class I32Constant final : public IntegerConstant {
public:
    explicit I32Constant(int32_t value) : value_(value) {}

    int32_t value() const {
        return value_;
    }

    int64_t signExtendedValue() const override {
        return ops::SExt<int64_t>()(value());
    }

    int64_t zeroExtendedValue() const override {
        return ops::ZExt<int64_t>()(value());
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitI32Constant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitI32Constant(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<I32>();
    }

    std::string format() const override {
        return std::to_string(value());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<I32Constant>(value());
    }

protected:
    bool equals(const Constant &other) const override {
        return typeid(*this) == typeid(other) && value() == static_cast<const I32Constant &>(other).value();
    }

private:
    int32_t value_;
};

} // namespace ir
