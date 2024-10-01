#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "mir/Immediate.h"
#include "mir/ImmediateOperand.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

namespace mir {

class MemoryOperand {
public:
    explicit MemoryOperand(std::shared_ptr<Register> baseReg,
                           std::unique_ptr<Immediate> offset)
        : baseReg_(RegisterKind::kInteger, std::move(baseReg)), offset_(std::move(offset)) {}

    template <typename Self>
    auto &baseReg(this Self &&self) {
        return self.baseReg_;
    }

    template <typename Self>
    auto &offset(this Self &&self) {
        return self.offset_;
    }

    std::string format() const {
        return std::format("{}({})", *offset(), *baseReg());
    }

    MemoryOperand clone() const {
        return MemoryOperand(share(*baseReg()), offset()->clone());
    }

private:
    RegisterOperand baseReg_;
    ImmediateOperand offset_;
};

} // namespace mir

template <>
struct std::formatter<mir::MemoryOperand> {
    constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    auto format(const mir::MemoryOperand &op, std::format_context &ctx) const {
        return std::format_to(ctx.out(), "{}", op.format());
    }
};
