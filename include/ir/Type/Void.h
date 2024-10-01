#pragma once

#include <memory>
#include <string>
#include <typeinfo>
#include <utility>

#include "ir/Constant.h"
#include "ir/Type.h"
#include "ir/TypeVisitor.h"

namespace ir {

class Void final : public Type {
public:
    int size() const override {
        std::unreachable();
    }

    int alignment() const override {
        std::unreachable();
    }

    std::unique_ptr<Constant> zeroValue() const override;

    std::string format() const override {
        return "void";
    }

    std::unique_ptr<Type> clone() const override {
        return std::make_unique<Void>();
    }

    void accept(TypeVisitor &visitor) override {
        visitor.visitVoid(*this);
    }

    void accept(TypeVisitor &visitor) const override {
        visitor.visitVoid(*this);
    }

protected:
    bool equals(const Type &other) const override {
        return typeid(*this) == typeid(other);
    }
};

} // namespace ir
