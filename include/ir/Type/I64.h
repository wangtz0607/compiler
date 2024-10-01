#pragma once

#include <memory>
#include <string>
#include <typeinfo>

#include "ir/Constant.h"
#include "ir/Type.h"
#include "ir/Type/IntegerType.h"
#include "ir/TypeVisitor.h"

namespace ir {

class I64 final : public IntegerType {
public:
    int size() const override {
        return 8;
    }

    int alignment() const override {
        return 8;
    }

    std::unique_ptr<Constant> zeroValue() const override;

    std::string format() const override {
        return "i64";
    }

    std::unique_ptr<Type> clone() const override {
        return std::make_unique<I64>();
    }

    void accept(TypeVisitor &visitor) override {
        visitor.visitI64(*this);
    }

    void accept(TypeVisitor &visitor) const override {
        visitor.visitI64(*this);
    }

protected:
    bool equals(const Type &other) const override {
        return typeid(*this) == typeid(other);
    }
};

} // namespace ir
