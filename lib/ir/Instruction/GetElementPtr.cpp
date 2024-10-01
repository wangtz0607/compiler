#include "ir/Instruction/GetElementPtr.h"

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ir/Type.h"
#include "ir/Type/IntegerType.h"
#include "ir/Use.h"
#include "ir/Value.h"
#include "utils/Memory.h"
#include "utils/StringJoiner.h"

using namespace ir;

GetElementPtr::GetElementPtr(std::unique_ptr<Type> sourceType,
                             std::shared_ptr<Value> ptr,
                             std::vector<std::shared_ptr<Value>> indices)
        : sourceType_(std::move(sourceType)), ptr_(this, std::move(ptr)) {
    for (auto &idx : indices) {
        indices_.push_back(std::make_unique<Use<Value, IntegerType>>(this, std::move(idx)));
    }
}

std::unordered_set<const UseBase *> GetElementPtr::operands() const {
    std::unordered_set<const UseBase *> operands;
    operands.insert(&ptr());
    for (const UseBase &idx : indices(*this)) {
        operands.insert(&idx);
    }
    return operands;
}

std::string GetElementPtr::format() const {
    StringJoiner formattedIndices(", ");
    for (const Use<Value, IntegerType> &idx : indices(*this)) {
        formattedIndices.addFormat("{} {:o}", *idx->type(), *idx);
    }
    return std::format(
        "{:o} = getelementptr {}, {} {:o}, {}",
        *this, *sourceType(), *ptr()->type(), *ptr(), formattedIndices);
}

std::unique_ptr<Value> GetElementPtr::clone() const {
    std::vector<std::shared_ptr<Value>> clonedIndices;
    for (const Use<Value, IntegerType> &idx : indices(*this)) {
        clonedIndices.push_back(share(*idx));
    }
    return std::make_unique<GetElementPtr>(sourceType(), share(*ptr()), std::move(clonedIndices));
}
