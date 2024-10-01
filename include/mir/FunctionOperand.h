#pragma once

#include "mir/Function.h"

namespace mir {

class FunctionOperand {
public:
    explicit FunctionOperand(Function *function) : function_(function) {}

    Function &operator*() const {
        return *function_;
    }

    Function *operator->() const {
        return function_;
    }

    void set(Function *function) {
        function_ = function;
    }

private:
    Function *function_;
};

} // namespace mir
