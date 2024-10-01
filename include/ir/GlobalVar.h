#pragma once

#include <memory>
#include <optional>

#include "common/Linkage.h"
#include "ir/Constant.h"
#include "ir/ConstantVisitor.h"
#include "ir/GlobalValue.h"
#include "ir/Type.h"
#include "ir/Use.h"

namespace ir {

class GlobalVar final : public GlobalValue {
public:
    GlobalVar(std::unique_ptr<Type> valueType,
              Linkage linkage,
              std::optional<std::shared_ptr<Constant>> initializer = std::nullopt);

    std::unique_ptr<Type> valueType() const {
        return valueType_->clone();
    }

    Linkage linkage() const {
        return linkage_;
    }

    bool hasInitializer() const {
        return initializer_.has_value();
    }

    Constant &initializer() const {
        return *initializer_.value();
    }

    void setInitializer(std::optional<std::shared_ptr<Constant>> initializer);

    void accept(ConstantVisitor &visitor) override {
        visitor.visitGlobalVar(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitGlobalVar(*this);
    }

    std::string format() const override;

private:
    std::unique_ptr<Type> valueType_;
    Linkage linkage_;
    std::optional<Use<Constant>> initializer_;
};

} // namespace ir
