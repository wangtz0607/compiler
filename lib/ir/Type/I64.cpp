#include "ir/Type/I64.h"

#include <memory>

#include "ir/Constant/I64Constant.h"
#include "ir/Type.h"

using namespace ir;

std::unique_ptr<Constant> I64::zeroValue() const {
    return std::make_unique<I64Constant>(0);
}
