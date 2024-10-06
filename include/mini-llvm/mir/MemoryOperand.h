#pragma once

#include <format>
#include <memory>
#include <string>
#include <utility>

#include "mini-llvm/mir/Immediate.h"
#include "mini-llvm/mir/ImmediateOperand.h"
#include "mini-llvm/mir/Register.h"
#include "mini-llvm/mir/RegisterKind.h"
#include "mini-llvm/mir/RegisterOperand.h"
#include "mini-llvm/utils/Memory.h"

namespace mini_llvm::mir {

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

} // namespace mini_llvm::mir

template <>
struct std::formatter<mini_llvm::mir::MemoryOperand> {
    constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    auto format(const mini_llvm::mir::MemoryOperand &op, std::format_context &ctx) const {
        return std::format_to(ctx.out(), "{}", op.format());
    }
};
