#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "ir/Instruction.h"
#include "ir/InstructionVisitor.h"
#include "ir/Type.h"
#include "ir/Type/Ptr.h"
#include "ir/Type/Void.h"
#include "ir/Use.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class Store final : public Instruction {
public:
    Store(std::shared_ptr<Value> value, std::shared_ptr<Value> addr)
        : value_(this, std::move(value)), ptr_(this, std::move(addr)) {}

    template <typename Self>
    auto &value(this Self &&self) {
        return self.value_;
    }

    template <typename Self>
    auto &ptr(this Self &&self) {
        return self.ptr_;
    }

    std::unordered_set<const UseBase *> operands() const override {
        return {&value(), &ptr()};
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitStore(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitStore(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<Void>();
    }

    std::string format() const override {
        return std::format("store {} {:o}, {} {:o}", *value()->type(), *value(), *ptr()->type(), *ptr());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<Store>(share(*value()), share(*ptr()));
    }

private:
    Use<Value> value_;
    Use<Value, Ptr> ptr_;
};

} // namespace ir
