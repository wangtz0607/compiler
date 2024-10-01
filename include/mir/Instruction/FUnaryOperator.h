#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "common/Precision.h"
#include "mir/Formatting.h"
#include "mir/Instruction.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"

namespace mir {

class FUnaryOperator : public Instruction {
public:
    Precision precision() const {
        return precision_;
    }

    template <typename Self>
    auto &dst(this Self &&self) {
        return self.dst_;
    }

    template <typename Self>
    auto &src(this Self &&self) {
        return self.src_;
    }

    std::unordered_set<const RegisterOperand *> regOps() const override {
        return {&dst(), &src()};
    }

    std::unordered_set<const RegisterOperand *> dsts() const override {
        return {&dst()};
    }

    std::unordered_set<const RegisterOperand *> srcs() const override {
        return {&src()};
    }

    std::string format() const override {
        return std::format("{}<{}> {}, {}", mnemonic(), specifier(precision()), *dst(), *src());
    }

protected:
    FUnaryOperator(Precision precision, std::shared_ptr<Register> dst, std::shared_ptr<Register> src)
        : precision_(precision),
          dst_(RegisterKind::kFloating, std::move(dst)),
          src_(RegisterKind::kFloating, std::move(src)) {}

    virtual const char *mnemonic() const = 0;

private:
    Precision precision_;
    RegisterOperand dst_, src_;
};

} // namespace mir
