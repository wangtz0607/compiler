#pragma once

#include <string>

#include "ir/ConstantVisitor.h"
#include "ir/Value.h"

namespace ir {

class Constant : public Value {
public:
    virtual void accept(ConstantVisitor &visitor) = 0;
    virtual void accept(ConstantVisitor &visitor) const = 0;

    std::string formatAsOperand() const override {
        return format();
    }

protected:
    virtual bool equals(const Constant &other) const = 0;

    friend bool operator==(const Constant &lhs, const Constant &rhs);
};

inline bool operator==(const Constant &lhs, const Constant &rhs) {
    return lhs.equals(rhs);
}

} // namespace ir
