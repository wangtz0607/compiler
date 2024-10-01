#pragma once

#include <exception>

#include "ir/Function.h"
#include "ir/Module.h"
#include "opt/ir/FunctionAnalysis.h"
#include "opt/ir/ModuleAnalysis.h"

namespace ir {

class VerificationException : public std::exception {
public:
    constexpr const char *what() const noexcept override {
        return "VerificationException";
    }

private:
    std::string message_;
};

class VerificationAnalysis final : public FunctionAnalysis, public ModuleAnalysis {
public:
    void runOnFunction(const Function &F) override;
    void runOnModule(const Module &M) override;
};

} // namespace ir
