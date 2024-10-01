#pragma once

#include <cstdint>
#include <format>
#include <memory>
#include <utility>

#include "ir/Constant.h"
#include "ir/Type.h"
#include "ir/Type/Ptr.h"
#include "ir/Value.h"

namespace ir {

class GlobalValue : public Constant {
public:
    std::unique_ptr<Type> type() const override {
        return std::make_unique<Ptr>();
    }

    std::string formatAsOperand() const override {
        return "@" + (!name().empty() ? name() : std::format("{:x}", reinterpret_cast<uintptr_t>(this)));
    }

    std::unique_ptr<Value> clone() const override {
        std::unreachable();
    }

protected:
    bool equals(const Constant &) const override {
        std::unreachable();
    }
};

} // namespace ir
