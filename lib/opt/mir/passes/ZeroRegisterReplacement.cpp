#include "opt/mir/passes/ZeroRegisterReplacement.h"

#include <memory>
#include <unordered_set>
#include <utility>
#include <vector>

#include "mir/BasicBlock.h"
#include "mir/Immediate.h"
#include "mir/Instruction.h"
#include "mir/Instruction/LI.h"
#include "mir/Instruction/Mov.h"
#include "mir/IntegerImmediate.h"
#include "mir/Register.h"
#include "mir/RegisterOperand.h"
#include "utils/Memory.h"

using namespace mir;

bool ZeroRegisterReplacement::runOnBasicBlock(BasicBlock &B) {
    bool changed = false;

    bool changed2;
    do {
        changed2 = false;

        std::unordered_set<Register *> zeros;

        for (Instruction &I : B) {
            for (Register *reg : def(I)) {
                zeros.erase(reg);
            }
            if (auto *li = dynamic_cast<const LI *>(&I)) {
                if (auto *src = dynamic_cast<const IntegerImmediate *>(&*li->src())) {
                    if (src->value() == 0) {
                        Register *dst = &*li->dst();
                        zeros.insert(dst);
                    }
                }
            }
            for (RegisterOperand *op : I.srcs()) {
                if (zeros.contains(&**op)) {
                    if (&**op != zeroReg_) {
                        op->set(share(*zeroReg_));
                        changed2 = true;
                    }
                }
            }
        }

        std::vector<std::pair<BasicBlock::const_iterator, std::unique_ptr<Instruction>>> replace;

        for (BasicBlock::const_iterator i = B.begin(); i != B.end(); ++i) {
            if (auto *mov = dynamic_cast<const Mov *>(&*i)) {
                if (&*mov->src() == zeroReg_) {
                    int width = mov->width();
                    std::shared_ptr<Register> dst = share(*mov->dst());
                    std::unique_ptr<Immediate> src = std::make_unique<IntegerImmediate>(0);
                    replace.emplace_back(i, std::make_unique<LI>(width, std::move(dst), std::move(src)));
                }
            }
        }

        for (auto &[i, I] : replace) {
            B.add(i, std::move(I));
            B.remove(i);
            changed2 = true;
        }

        changed |= changed2;
    } while (changed2);

    return changed;
}
