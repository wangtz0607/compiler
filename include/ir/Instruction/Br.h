#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "ir/BasicBlock.h"
#include "ir/Instruction/Terminator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Type.h"
#include "ir/Type/Void.h"
#include "ir/Use.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class Br final : public Terminator {
public:
    explicit Br(std::weak_ptr<BasicBlock> dest) : dest_(this, std::move(dest)) {}

    template <typename Self>
    auto &dest(this Self &&self) {
        return self.dest_;
    }

    std::unordered_set<BasicBlock *> successors() const override {
        return {&*dest()};
    }

    std::unordered_set<const UseBase *> operands() const override {
        return {&dest()};
    }

    void accept(InstructionVisitor &visitor) override {
        visitor.visitBr(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitBr(*this);
    }

    std::unique_ptr<Type> type() const override {
        return std::make_unique<Void>();
    }

    std::string format() const override {
        return std::format("br {} {:o}", *dest()->type(), *dest());
    }

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<Br>(weaken(*dest()));
    }

private:
    Use<BasicBlock> dest_;
};

} // namespace ir
