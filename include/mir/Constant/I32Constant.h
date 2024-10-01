#pragma once

#include <cstdint>
#include <format>
#include <string>

#include "mir/Constant.h"
#include "mir/ConstantVisitor.h"

namespace mir {

class I32Constant final : public Constant {
public:
    explicit I32Constant(int32_t value) : value_(value) {}

    int32_t value() const {
        return value_;
    }

    void setValue(int32_t value) {
        value_ = value;
    }

    int size() const override {
        return 4;
    }

    std::string format() const override {
        return std::format("i32 {}", value());
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitI32Constant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitI32Constant(*this);
    }

private:
    int32_t value_;
};

} // namespace mir
