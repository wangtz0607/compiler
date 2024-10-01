#include "ir/Type/Double.h"

#include <memory>

#include "ir/Constant/DoubleConstant.h"
#include "ir/Type.h"

using namespace ir;

std::unique_ptr<Constant> Double::zeroValue() const {
    return std::make_unique<DoubleConstant>(0.);
}
