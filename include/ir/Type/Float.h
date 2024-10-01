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

class Float final : public FloatingType {
public:
    Precision precision() const override {
        return Precision::kSingle;
    }

    int size() const override {
        return 4;
    }

    int alignment() const override {
        return 4;
    }

    std::unique_ptr<Constant> zeroValue() const override;

    std::string format() const override {
        return "float";
    }

    std::unique_ptr<Type> clone() const override {
        return std::make_unique<Float>();
    }

    void accept(TypeVisitor &visitor) override {
        visitor.visitFloat(*this);
    }

    void accept(TypeVisitor &visitor) const override {
        visitor.visitFloat(*this);
    }

protected:
    bool equals(const Type &other) const override {
        return typeid(*this) == typeid(other);
    }
};

} // namespace ir
