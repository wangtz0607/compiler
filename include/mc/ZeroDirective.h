#pragma once

#include <format>
#include <string>

#include "mc/Directive.h"

namespace mc {

class ZeroDirective : public Directive {
public:
    int size() const {
        return size_;
    }

    void setSize(int size) {
        size_ = size;
    }

    std::string format() const override {
        return std::format(".{} {}", directiveName(), size());
    }

protected:
    explicit ZeroDirective(int size) : size_(size) {}

    virtual std::string directiveName() const = 0;

private:
    int size_;
};

} // namespace mc
