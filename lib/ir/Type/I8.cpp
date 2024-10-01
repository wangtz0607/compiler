#include "ir/Type/I8.h"

#include <cstdint>
#include <memory>

#include "ir/Constant/I8Constant.h"
#include "ir/Type.h"

using namespace ir;

std::unique_ptr<Constant> I8::zeroValue() const {
    return std::make_unique<I8Constant>(static_cast<uint8_t>(0));
}
