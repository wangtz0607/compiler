#include "opt/mc/FragmentTransform.h"

#include "mc/Fragment.h"
#include "mc/Program.h"

using namespace mc;

bool FragmentTransform::runOnProgram(Program &program) {
    bool changed = false;
    for (Fragment &fragment : program) {
        changed |= runOnFragment(fragment);
    }
    return changed;
}
