#pragma once

#include <string>
#include <unordered_map>

#include "mc/Fragment.h"
#include "mc/Program.h"
#include "mir/BasicBlock.h"
#include "mir/Function.h"
#include "mir/GlobalVar.h"
#include "mir/Module.h"

class RISCVMCGen {
public:
    RISCVMCGen(const mir::Module *MM, mc::Program *program) : MM_(MM), program_(program) {}

    void emit();

private:
    const mir::Module *MM_;
    mc::Program *program_;
    std::unordered_map<const mir::BasicBlock *, std::string> labelMap_;

    void emitGlobalVar(const mir::GlobalVar &G, mc::Fragment &fragment);
    void emitFunction(const mir::Function &F, mc::Fragment &fragment);
};
