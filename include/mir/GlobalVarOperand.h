#pragma once

#include "mir/GlobalVar.h"

namespace mir {

class GlobalVarOperand {
public:
    explicit GlobalVarOperand(GlobalVar *globalVar) : globalVar_(globalVar) {}

    GlobalVar &operator*() const {
        return *globalVar_;
    }

    GlobalVar *operator->() const {
        return globalVar_;
    }

    void set(GlobalVar *globalVar) {
        globalVar_ = globalVar;
    }

private:
    GlobalVar *globalVar_;
};

} // namespace mir
