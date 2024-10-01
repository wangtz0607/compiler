#pragma once

#include <memory>
#include <string>
#include <typeinfo>

#include "common/Precision.h"
#include "ir/Constant.h"
#include "ir/Type.h"
#include "ir/Type/FloatingType.h"
#include "ir/TypeVisitor.h"

namespace ir {

class Double final : public FloatingType {
public:
    Precision precision() const override {
        return Precision::kDouble;
    }

    int size() const override {
        return 8;
    }

    int alignment() const override {
        return 8;
    }

    std::unique_ptr<Constant> zeroValue() const override;

    std::string format() const override {
        return "double";
    }

    std::unique_ptr<Type> clone() const override {
        return std::make_unique<Double>();
    }

    void accept(TypeVisitor &visitor) override {
        visitor.visitDouble(*this);
    }

    void accept(TypeVisitor &visitor) const override {
        visitor.visitDouble(*this);
    }

protected:
    bool equals(const Type &other) const override {
        return typeid(*this) == typeid(other);
    }
};

} // namespace ir
