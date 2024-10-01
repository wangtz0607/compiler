#include "mir/StackSlot.h"

#include <cassert>

#include "mir/StackFrame.h"

using namespace mir;

int StackSlot::offset() const {
    assert(frame_ != nullptr);
    frame_->computeOffsets();
    return offset_;
}
