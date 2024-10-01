#pragma once

#include <string>

#include "mc/Operand.h"

namespace mc {

class RegisterOperand : public Operand {
public:
    explicit RegisterOperand(int idx) : idx_(idx) {}

    int idx() const {
        return idx_;
    }

    void setIdx(int idx) {
        idx_ = idx;
    }

    std::string format() const override {
        return name(idx());
    }

protected:
    virtual std::string name(int idx) const = 0;

private:
    int idx_;
};

} // namespace mc
