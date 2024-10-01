#pragma once

#include <functional>
#include <unordered_set>

#include "codegen/RegisterAllocator.h"
#include "mir/BasicBlockBuilder.h"
#include "mir/Function.h"
#include "mir/PhysicalRegister.h"
#include "mir/StackSlot.h"
#include "mir/VirtualRegister.h"

class NaiveAllocator : public RegisterAllocator {
public:
    void allocate(mir::Function &F,
                  int regWidth,
                  const std::unordered_set<mir::VirtualRegister *> &virtRegs,
                  const std::unordered_set<mir::PhysicalRegister *> &physRegs,
                  std::function<void (mir::PhysicalRegister *physReg, mir::StackSlot *slot, const mir::BasicBlockBuilder &builder)> load,
                  std::function<void (mir::PhysicalRegister *physReg, mir::StackSlot *slot, const mir::BasicBlockBuilder &builder)> store) override;
};
