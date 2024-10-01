#pragma once

#include <format>
#include <string>

#include "mir/Constant.h"
#include "mir/ConstantVisitor.h"

namespace mir {

class ZeroConstant final : public Constant {
public:
    explicit ZeroConstant(int size) : size_(size) {}

    int size() const override {
        return size_;
    }

    void setSize(int size) {
        size_ = size;
    }

    std::string format() const override {
        return std::format("zero {}", size());
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitZeroConstant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitZeroConstant(*this);
    }

private:
    int size_;
};

} // namespace mir
