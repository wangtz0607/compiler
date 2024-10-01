#include "ir/Instruction/Select.h"

#include <memory>

#include "ir/Constant.h"
#include "ir/Constant/I1Constant.h"
#include "ir/Constant/PoisonValue.h"
#include "utils/Memory.h"

using namespace ir;

std::unique_ptr<Constant> Select::fold() const {
    if (dynamic_cast<const PoisonValue *>(&*cond())) {
        return std::make_unique<PoisonValue>(type());
    }
    if (static_cast<const I1Constant *>(&*cond())->value() == true) {
        return cast<Constant>(trueValue()->clone());
    } else {
        return cast<Constant>(falseValue()->clone());
    }
}
