#include "ir/Type/Float.h"

#include <memory>

#include "ir/Constant/FloatConstant.h"
#include "ir/Type.h"

using namespace ir;

std::unique_ptr<Constant> Float::zeroValue() const {
    return std::make_unique<FloatConstant>(0.f);
}
