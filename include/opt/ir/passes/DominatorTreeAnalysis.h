#pragma once

#include <memory>
#include <vector>

#include "ir/Function.h"
#include "ir/Instruction.h"
#include "opt/ir/FunctionAnalysis.h"

namespace ir {

struct DominatorTreeNode {
    const BasicBlock *block;
    const DominatorTreeNode *parent;
    std::vector<const DominatorTreeNode *> children;
};

class DominatorTreeAnalysis final : public FunctionAnalysis {
public:
    DominatorTreeAnalysis();
    ~DominatorTreeAnalysis() override;
    void runOnFunction(const Function &F) override;
    const DominatorTreeNode *node(const BasicBlock &v) const;
    bool dominates(const BasicBlock &u, const BasicBlock &v) const;
    bool dominates(const Instruction &u, const Instruction &v) const;

private:
    class Impl;

    std::unique_ptr<Impl> impl_;
};

} // namespace ir
