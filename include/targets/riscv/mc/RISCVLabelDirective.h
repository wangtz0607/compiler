#pragma once

#include <string>
#include <utility>

#include "mc/LabelDirective.h"

namespace mc {

class RISCVLabelDirective final : public LabelDirective {
public:
    explicit RISCVLabelDirective(std::string labelName)
        : LabelDirective(std::move(labelName)) {}

protected:
    std::string directiveName() const override {
        return "dword";
    }
};

} // namespace mc
