#pragma once

#include <memory>
#include <utility>

#include "mir/Register.h"
#include "mir/RegisterKind.h"

namespace mir {

class RegisterOperand {
public:
    RegisterOperand(RegisterKind kind, std::shared_ptr<Register> reg)
        : kind_(kind), reg_(std::move(reg)) {}

    RegisterKind kind() const {
        return kind_;
    }

    Register &operator*() const {
        return *reg_;
    }

    Register *operator->() const {
        return &*reg_;
    }

    void set(std::shared_ptr<Register> reg) {
        reg_ = std::move(reg);
    }

private:
    RegisterKind kind_;
    std::shared_ptr<Register> reg_;
};

} // namespace mir
