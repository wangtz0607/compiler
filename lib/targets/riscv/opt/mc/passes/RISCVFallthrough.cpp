#include "targets/riscv/opt/mc/passes/RISCVFallthrough.h"

#include <iterator>
#include <vector>

#include "mc/Fragment.h"
#include "mc/Label.h"
#include "mc/LabelOperand.h"
#include "mc/Section.h"
#include "targets/riscv/mc/RISCVInstruction.h"
#include "targets/riscv/mc/RISCVOperation.h"

using namespace mc;

bool RISCVFallthrough::runOnFragment(Fragment &fragment) {
    if (fragment.section() != Section::kText) return false;

    std::vector<Fragment::const_iterator> remove;

    for (Fragment::const_iterator i = fragment.begin(), j = std::next(i); j != fragment.end(); ++i, ++j) {
        if (auto *I = dynamic_cast<const RISCVInstruction *>(&*i)) {
            if (I->opcode() == RISCV_J) {
                if (auto *labelOp = dynamic_cast<const LabelOperand *>(&*I->operand_begin())) {
                    if (auto *label = dynamic_cast<const Label *>(&*j)) {
                        if (labelOp->labelName() == label->labelName()) {
                            remove.push_back(i);
                        }
                    }
                }
            }
        }
    }

    bool changed = false;

    for (Fragment::const_iterator i : remove) {
        fragment.remove(i);
        changed = true;
    }

    return changed;
}
