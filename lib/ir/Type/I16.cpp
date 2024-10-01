#include "ir/Type/I16.h"

#include <cstdint>
#include <memory>

#include "ir/Constant/I16Constant.h"
#include "ir/Type.h"

using namespace ir;

std::unique_ptr<Constant> I16::zeroValue() const {
    return std::make_unique<I16Constant>(static_cast<uint16_t>(0));
}
