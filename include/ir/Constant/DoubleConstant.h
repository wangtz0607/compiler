#pragma once

#include <bit>
#include <cstdint>
#include <format>
#include <memory>
#include <string>
#include <typeinfo>

#include "ir/Constant/FloatingConstant.h"
#include "ir/ConstantVisitor.h"
#include "ir/Type.h"
#include "ir/Type/Double.h"
#include "ir/Value.h"

namespace ir {

class DoubleConstant final : public FloatingConstant {
public:
    explicit DoubleConstant(double value) : value_(value) {}

    double value() const {
        return value_;
    }

    uint64_t bitPattern() const override {
        return std::bit_cast<uint64_t>(value_);
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitDoubleConstant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitDoubleConstant(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<Double>();
    }

    std::string format() const override {
        return std::format("0x{:016x}", std::bit_cast<uint64_t>(value()));
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<DoubleConstant>(value());
    }

protected:
    bool equals(const Constant &other) const override {
        return typeid(*this) == typeid(other)
            && std::bit_cast<uint64_t>(value()) == std::bit_cast<uint64_t>(static_cast<const DoubleConstant &>(other).value());
    }

private:
    double value_;
};

} // namespace ir
