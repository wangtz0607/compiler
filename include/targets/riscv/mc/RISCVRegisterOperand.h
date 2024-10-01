#pragma once

#include <string>

#include "mc/RegisterOperand.h"
#include "targets/riscv/mc/RISCVRegister.h"

namespace mc {

class RISCVRegisterOperand final : public RegisterOperand {
public:
    explicit RISCVRegisterOperand(int idx) : RegisterOperand(idx) {}

protected:
    std::string name(int idx) const override {
        return mc::name(static_cast<RISCVRegister>(idx));
    }
};

} // namespace mc
