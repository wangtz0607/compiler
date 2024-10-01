#pragma once

#include <cstdint>
#include <format>
#include <string>

#include "mir/Constant.h"
#include "mir/ConstantVisitor.h"

namespace mir {

class I8Constant final : public Constant {
public:
    explicit I8Constant(int8_t value) : value_(value) {}

    int8_t value() const {
        return value_;
    }

    void setValue(int8_t value) {
        value_ = value;
    }

    int size() const override {
        return 1;
    }

    std::string format() const override {
        return std::format("i8 {}", value());
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitI8Constant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitI8Constant(*this);
    }

private:
    int8_t value_;
};

} // namespace mir
