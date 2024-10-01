#include "opt/mir/passes/IdentityMoveElimination.h"

#include <list>

#include "mir/BasicBlock.h"
#include "mir/Instruction/Mov.h"
#include "mir/RegisterOperand.h"

using namespace mir;

bool IdentityMoveElimination::runOnBasicBlock(BasicBlock &B) {
    bool changed = false;

    std::list<BasicBlock::const_iterator> remove;

    for (auto i = B.begin(), e = B.end(); i != e; ++i) {
        if (auto *mov = dynamic_cast<Mov *>(&*i)) {
            if (&*mov->dst() == &*mov->src()) {
                remove.emplace_back(i);
            }
        }
    }

    for (auto i : remove) {
        B.remove(i);
        changed = true;
    }

    return changed;
}
