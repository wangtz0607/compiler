#pragma once

#include <format>
#include <string>
#include <utility>

#include "mc/Directive.h"

namespace mc {

class LabelDirective : public Directive {
public:
    const std::string &labelName() const {
        return labelName_;
    }

    void setLabelName(std::string labelName) {
        labelName_ = std::move(labelName);
    }

    std::string format() const override {
        return std::format(".{} {}", directiveName(), labelName());
    }

protected:
    explicit LabelDirective(std::string labelName) : labelName_(std::move(labelName)) {}

    virtual std::string directiveName() const = 0;

private:
    std::string labelName_;
};

} // namespace mc
