#include "ir/Type/Ptr.h"

#include <memory>

#include "ir/Constant/NullPtrConstant.h"
#include "ir/Type.h"

using namespace ir;

std::unique_ptr<Constant> Ptr::zeroValue() const {
    return std::make_unique<NullPtrConstant>();
}
