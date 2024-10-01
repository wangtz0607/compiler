#pragma once

#include <string>

#include "mc/ZeroDirective.h"

namespace mc {

class RISCVZeroDirective final : public ZeroDirective {
public:
    explicit RISCVZeroDirective(int size) : ZeroDirective(size) {}

protected:
    std::string directiveName() const override {
        return "zero";
    }
};

} // namespace mc
