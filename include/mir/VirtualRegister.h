#pragma once

#include <cstdint>
#include <format>
#include <string>
#include <utility>

#include "mir/Register.h"

namespace mir {

class VirtualRegister final : public Register {
public:
    const std::string &name() const {
        return name_;
    }

    void setName(std::string name) {
        name_ = std::move(name);
    }

    std::string format() const override {
        return "$" + (!name().empty() ? name() : std::format("{:x}", reinterpret_cast<uintptr_t>(this)));
    }

private:
    std::string name_;
};

} // namespace mir
