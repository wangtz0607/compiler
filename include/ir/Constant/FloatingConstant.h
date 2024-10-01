#pragma once

#include <memory>

#include "ir/Constant.h"
#include "ir/Type.h"

namespace ir {

class FloatingConstant : public Constant {
public:
    virtual uint64_t bitPattern() const = 0;
};

std::unique_ptr<FloatingConstant> createFloatingConstant(std::unique_ptr<Type> type, double value);

} // namespace ir
