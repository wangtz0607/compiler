#pragma once

#include <memory>
#include <unordered_set>

#include "mir/BasicBlock.h"
#include "mir/Function.h"
#include "mir/Instruction.h"
#include "mir/Register.h"
#include "opt/mir/FunctionAnalysis.h"

namespace mir {

class LiveVariableAnalysis final : public FunctionAnalysis {
public:
    LiveVariableAnalysis();
    ~LiveVariableAnalysis() override;
    void runOnFunction(const Function &F) override;
    std::unordered_set<Register *> liveIn(const BasicBlock &B) const;
    std::unordered_set<Register *> liveOut(const BasicBlock &B) const;
    std::unordered_set<Register *> liveIn(const Instruction &I) const;
    std::unordered_set<Register *> liveOut(const Instruction &I) const;

private:
    class Impl;

    std::unique_ptr<Impl> impl_;
};

} // namespace mir
