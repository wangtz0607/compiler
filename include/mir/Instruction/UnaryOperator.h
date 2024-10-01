#pragma once

#include <format>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "common/ExtensionMode.h"
#include "mir/Formatting.h"
#include "mir/Instruction.h"
#include "mir/Register.h"
#include "mir/RegisterKind.h"
#include "mir/RegisterOperand.h"

namespace mir {

class UnaryOperator : public Instruction {
public:
    int width() const {
        return width_;
    }

    template <typename Self>
    auto &dst(this Self &&self) {
        return self.dst_;
    }

    template <typename Self>
    auto &src(this Self &&self) {
        return self.src_;
    }

    ExtensionMode extensionMode() const {
        return extensionMode_;
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
        return std::format(
            "{}<{}> {}, {}, {}",
            mnemonic(), width(), *dst(), *src(), specifier(extensionMode()));
    }

protected:
    UnaryOperator(int width,
                  std::shared_ptr<Register> dst,
                  std::shared_ptr<Register> src,
                  ExtensionMode extensionMode)
        : width_(width),
          dst_(RegisterKind::kInteger, std::move(dst)),
          src_(RegisterKind::kInteger, std::move(src)),
          extensionMode_(extensionMode) {}

    virtual const char *mnemonic() const = 0;

private:
    int width_;
    RegisterOperand dst_, src_;
    ExtensionMode extensionMode_;
};

} // namespace mir
