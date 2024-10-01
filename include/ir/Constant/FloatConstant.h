#pragma once

#include <bit>
#include <cstdint>
#include <format>
#include <memory>
#include <string>
#include <typeinfo>

#include "common/ops/ZExt.h"
#include "ir/Constant/FloatingConstant.h"
#include "ir/ConstantVisitor.h"
#include "ir/Type.h"
#include "ir/Type/Float.h"
#include "ir/Value.h"

namespace ir {

class FloatConstant final : public FloatingConstant {
public:
    explicit FloatConstant(float value) : value_(value) {}

    float value() const {
        return value_;
    }

    uint64_t bitPattern() const override {
        return ops::ZExt<uint64_t>()(std::bit_cast<uint32_t>(value_));
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitFloatConstant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitFloatConstant(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<Float>();
    }

    std::string format() const override {
        return std::format("0x{:16x}", std::bit_cast<uint64_t>(static_cast<double>(value())));
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<FloatConstant>(value());
    }

protected:
    bool equals(const Constant &other) const override {
        return typeid(*this) == typeid(other)
            && std::bit_cast<uint32_t>(value()) == std::bit_cast<uint32_t>(static_cast<const FloatConstant &>(other).value());
    }

private:
    float value_;
};

} // namespace ir
