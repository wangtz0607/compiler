#pragma once

#include <format>
#include <string>

#include "mir/Constant.h"
#include "mir/ConstantVisitor.h"
#include "mir/GlobalVar.h"

namespace mir {

class PtrConstant final : public Constant {
public:
    PtrConstant(int size, GlobalVar *ptr) : size_(size), ptr_(ptr) {}

    GlobalVar *ptr() const {
        return ptr_;
    }

    void setGlobalVar(GlobalVar *ptr) {
        ptr_ = ptr;
    }

    int size() const override {
        return size_;
    }

    std::string format() const override {
        return std::format("ptr<{}> {:o}", size(), *ptr());
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitPtrConstant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitPtrConstant(*this);
    }

private:
    int size_;
    GlobalVar *ptr_;
};

} // namespace mir
