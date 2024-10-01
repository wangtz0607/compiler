#pragma once

#include <string>

#include "mir/Register.h"
#include "mir/RegisterKind.h"

namespace mir {

class PhysicalRegister : public Register {
public:
    virtual int idx() const = 0;
    virtual std::string name() const = 0;
    virtual RegisterKind kind() const = 0;
    virtual bool isVolatile() const = 0;
    virtual bool isAllocatable() const = 0;

    std::string format() const override {
        return "%" + name();
    }
};

} // namespace mir
