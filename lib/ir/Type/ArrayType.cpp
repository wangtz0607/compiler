#include "ir/Type/ArrayType.h"

#include <memory>
#include <typeinfo>
#include <vector>

#include "ir/Constant.h"
#include "ir/Constant/ArrayConstant.h"
#include "ir/Type.h"
#include "utils/Memory.h"

using namespace ir;

std::unique_ptr<Constant> ArrayType::zeroValue() const {
    return std::make_unique<ArrayConstant>(cast<ArrayType>(clone()), std::vector<std::shared_ptr<Constant>>{});
}

bool ArrayType::equals(const Type &other) const {
    if (typeid(*this) == typeid(other)) {
        const ArrayType &castOther = static_cast<const ArrayType &>(other);
        return *elementType() == *castOther.elementType() && numElements() == castOther.numElements();
    }
    return false;
}
