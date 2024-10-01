#include "mir/Instruction/Terminator.h"

#include <unordered_set>
#include <utility>

using namespace mir;

std::unordered_set<BasicBlockOperand *> Terminator::successors() {
    std::unordered_set<BasicBlockOperand *> successors;
    for (const BasicBlockOperand *op : std::as_const(*this).successors()) {
        successors.insert(const_cast<BasicBlockOperand *>(op));
    }
    return successors;
}
