#include "ir/Type/I32.h"

#include <memory>

#include "ir/Constant/I32Constant.h"
#include "ir/Type.h"

using namespace ir;

std::unique_ptr<Constant> I32::zeroValue() const {
    return std::make_unique<I32Constant>(0);
}
