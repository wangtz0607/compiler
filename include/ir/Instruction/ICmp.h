#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "ir/Constant.h"
#include "ir/Instruction/BinaryIntegerRelationalOperator.h"
#include "ir/InstructionVisitor.h"
#include "ir/Value.h"
#include "utils/Memory.h"

namespace ir {

class ICmp final : public BinaryIntegerRelationalOperator {
public:
    enum Condition {
        kEQ,
        kNE,
        kSLT,
        kSGT,
        kSLE,
        kSGE,
        kULT,
        kUGT,
        kULE,
        kUGE,
    };

    ICmp(Condition cond, std::shared_ptr<Value> lhs, std::shared_ptr<Value> rhs)
        : BinaryIntegerRelationalOperator(std::move(lhs), std::move(rhs)), cond_(cond) {}

    Condition cond() const {
        return cond_;
    }

    void setCond(Condition cond) {
        cond_ = cond;
    }

    std::unique_ptr<Constant> fold() const override;

    void accept(InstructionVisitor &visitor) override {
        visitor.visitICmp(*this);
    }

    void accept(InstructionVisitor &visitor) const override {
        visitor.visitICmp(*this);
    }

    std::string format() const override;

    std::unique_ptr<Value> clone() const override {
        return std::make_unique<ICmp>(cond(), share(*lhs()), share(*rhs()));
    }

private:
    Condition cond_;
};

inline constexpr const char *specifier(ICmp::Condition cond) {
    using enum ICmp::Condition;
    switch (cond) {
        case kEQ: return "eq";
        case kNE: return "ne";
        case kSLT: return "slt";
        case kSGT: return "sgt";
        case kSLE: return "sle";
        case kSGE: return "sge";
        case kULT: return "ult";
        case kUGT: return "ugt";
        case kULE: return "ule";
        case kUGE: return "uge";
        default: std::unreachable();
    }
}

inline std::string ICmp::format() const {
    return std::format("{:o} = icmp {} {} {:o}, {:o}", *this, specifier(cond()), *opType(), *lhs(), *rhs());
}

} // namespace ir
