#include "ir/Type/Void.h"

#include <memory>

#include "ir/Constant/VoidValue.h"
#include "ir/Type.h"

using namespace ir;

std::unique_ptr<Constant> Void::zeroValue() const {
    return std::make_unique<VoidValue>();
}
