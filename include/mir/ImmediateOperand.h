#pragma once

#include <memory>
#include <utility>

#include "mir/Immediate.h"

namespace mir {

class ImmediateOperand {
public:
    explicit ImmediateOperand(std::unique_ptr<Immediate> imm) : imm_(std::move(imm)) {}

    const Immediate &operator*() const {
        return *imm_;
    }

    const Immediate *operator->() const {
        return &*imm_;
    }

    void set(std::unique_ptr<Immediate> imm) {
        imm_ = std::move(imm);
    }

private:
    std::unique_ptr<Immediate> imm_;
};

} // namespace mir
