#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <typeinfo>

#include "ir/Constant.h"
#include "ir/Constant/IntegerConstant.h"
#include "ir/ConstantVisitor.h"
#include "ir/Type.h"
#include "ir/Type/Ptr.h"
#include "ir/Value.h"

namespace ir {

class NullPtrConstant final : public IntegerConstant {
public:
    int64_t signExtendedValue() const override {
        return 0;
    }

    int64_t zeroExtendedValue() const override {
        return 0;
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitNullPtrConstant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitNullPtrConstant(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<Ptr>();
    }

    std::string format() const override {
        return "null";
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<NullPtrConstant>();
    }

protected:
    bool equals(const Constant &other) const override {
        return typeid(*this) == typeid(other);
    }
};

} // namespace ir
