#pragma once

#include <concepts>
#include <cstdint>
#include <format>
#include <memory>
#include <string>

namespace mir {

class Immediate {
public:
    virtual ~Immediate() = default;
    Immediate(const Immediate &) = delete;
    Immediate(Immediate &&) = delete;
    Immediate &operator=(const Immediate &) = delete;
    Immediate &operator=(Immediate &&) = delete;
    virtual int64_t value() const = 0;
    virtual std::unique_ptr<Immediate> clone() const = 0;

    std::string format() const {
        return std::to_string(value());
    }

protected:
    Immediate() = default;
};

} // namespace mir

template <typename ImmediateT>
    requires std::derived_from<ImmediateT, mir::Immediate>
struct std::formatter<ImmediateT> {
    constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    auto format(const ImmediateT &imm, std::format_context &ctx) const {
        return std::format_to(ctx.out(), "{}", imm.format());
    }
};
