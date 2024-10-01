#pragma once

#include <string>
#include <utility>

#include "mc/Instruction.h"
#include "mc/Operand.h"
#include "targets/riscv/mc/RISCVOperation.h"

namespace mc {

class RISCVInstruction final : public Instruction {
public:
    explicit RISCVInstruction(int opcode, std::vector<std::unique_ptr<Operand>> operands = {})
        : Instruction(opcode, std::move(operands)) {}

protected:
    std::string mnemonic(int opcode) const override {
        return mc::mnemonic(static_cast<RISCVOperation>(opcode));
    }
};

} // namespace mc
