#pragma once

#include "common/Precision.h"
#include "ir/Type.h"

namespace ir {

class FloatingType : public Type {
public:
    virtual Precision precision() const = 0;
};

} // namespace ir
