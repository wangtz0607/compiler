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
#include "ir/Type/I8.h"
#include "ir/Value.h"

namespace ir {

class I8Constant final : public IntegerConstant {
public:
    explicit I8Constant(int8_t value) : value_(value) {}

    int8_t value() const {
        return value_;
    }

    int64_t signExtendedValue() const override {
        return ops::SExt<int64_t>()(value());
    }

    int64_t zeroExtendedValue() const override {
        return ops::ZExt<int64_t>()(value());
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitI8Constant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitI8Constant(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<I8>();
    }

    std::string format() const override {
        return std::to_string(value());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<I8Constant>(value());
    }

protected:
    bool equals(const Constant &other) const override {
        return typeid(*this) == typeid(other) && value() == static_cast<const I8Constant &>(other).value();
    }

private:
    int8_t value_;
};

} // namespace ir
