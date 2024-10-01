#include "ir/Type/I1.h"

#include <memory>

#include "ir/Constant/I1Constant.h"
#include "ir/Type.h"

using namespace ir;

std::unique_ptr<Constant> I1::zeroValue() const {
    return std::make_unique<I1Constant>(false);
}
