#pragma once

#include <unordered_map>

#include "ir/Function.h"
#include "ir/GlobalVar.h"
#include "ir/Module.h"
#include "mir/Function.h"
#include "mir/GlobalVar.h"
#include "mir/Module.h"

class RISCVMIRGen {
public:
    RISCVMIRGen(const ir::Module *IM, mir::Module *MM) : IM_(IM), MM_(MM) {}

    void emit();

private:
    const ir::Module *IM_;
    mir::Module *MM_;
    std::unordered_map<const ir::GlobalVar *, mir::GlobalVar *> globalVarMap_;
    std::unordered_map<const ir::Function *, mir::Function *> functionMap_;

    void emitGlobalVar(const ir::GlobalVar &G, mir::GlobalVar &m_G);
    void emitFunction(const ir::Function &F, mir::Function &m_F);
};
