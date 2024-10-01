#include "ir/GlobalVar.h"

#include <cassert>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#include "common/Linkage.h"
#include "ir/Constant.h"
#include "ir/Value.h"
#include "utils/Memory.h"
#include "utils/StringJoiner.h"

using namespace ir;

GlobalVar::GlobalVar(std::unique_ptr<Type> valueType,
                     Linkage linkage,
                     std::optional<std::shared_ptr<Constant>> initializer)
        : valueType_(std::move(valueType)), linkage_(linkage) {
    if (initializer.has_value()) {
        assert(*initializer_.value()->type() == *valueType_);
        initializer_.emplace(this, std::move(initializer.value()));
    }
}

void GlobalVar::setInitializer(std::optional<std::shared_ptr<Constant>> initializer) {
    if (initializer.has_value()) {
        if (initializer_.has_value()) {
            initializer_.value().set(std::move(initializer.value()));
        } else {
            initializer_.emplace(this, std::move(initializer.value()));
        }
    } else {
        initializer_.reset();
    }
}

std::string GlobalVar::format() const {
    StringJoiner formatted(" ");
    formatted.addFormat("{} =", formatAsOperand());
    if (linkage() == Linkage::kInternal) {
        formatted.add("internal");
    }
    if (!hasInitializer()) {
        formatted.add("external");
    }
    formatted.addFormat("global {}", *valueType());
    if (hasInitializer()) {
        formatted.addFormat("{:o}", initializer());
    }
    return formatted.toString();
}
