#pragma once

#include <memory>
#include <string>

#include "ir/Constant.h"
#include "ir/ConstantVisitor.h"
#include "ir/Type.h"
#include "ir/Type/Void.h"
#include "ir/Value.h"

namespace ir {

class VoidValue final : public Constant {
public:
    void accept(ConstantVisitor &visitor) override {
        visitor.visitVoidValue(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitVoidValue(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<Void>();
    }

    std::string format() const override {
        std::unreachable();
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<VoidValue>();
    }

protected:
    bool equals(const Constant &other) const override {
        return typeid(*this) == typeid(other);
    }
};

} // namespace ir
