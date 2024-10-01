#pragma once

#include <utility>

#include "mir/InstructionVisitor.h"

namespace mir {

class RISCVCall;
class RISCVRet;

class RISCVInstructionVisitor : public InstructionVisitor {
public:
    virtual void visitRISCVCall(RISCVCall &I) { visitRISCVCall(std::as_const(I)); }
    virtual void visitRISCVRet(RISCVRet &I) { visitRISCVRet(std::as_const(I)); }

    virtual void visitRISCVCall(const RISCVCall &) { std::unreachable(); }
    virtual void visitRISCVRet(const RISCVRet &) { std::unreachable(); }
};

} // namespace mir
