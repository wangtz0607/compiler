#pragma once

#include <cstdint>
#include <format>
#include <string>

#include "mc/Operand.h"
#include "targets/riscv/mc/RISCVRegister.h"

namespace mc {

class RISCVMemoryOperand final : public Operand {
public:
    RISCVMemoryOperand(int idx, int64_t offset) : idx_(idx), offset_(offset) {}

    int idx() const {
        return idx_;
    }

    void setIdx(int idx) {
        idx_ = idx;
    }

    int64_t offset() const {
        return offset_;
    }

    void setOffset(int64_t offset) {
        offset_ = offset;
    }

    std::string format() const override {
        return std::format("{}({})", offset(), name(static_cast<RISCVRegister>(idx())));
    }

private:
    int idx_;
    int64_t offset_;
};

} // namespace mc
