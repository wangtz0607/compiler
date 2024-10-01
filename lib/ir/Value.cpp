#include "ir/Value.h"

#include <cassert>
#include <memory>

#include "ir/Use.h"

using namespace ir;

bool ir::replaceAllUsesWith(const Value &value, std::shared_ptr<Value> value2) {
    assert(*value2->type() == *value.type());

    bool changed = false;

    while (!value.use_empty()) {
        value.use_begin()->set(value2);
        changed = true;
    }

    return changed;
}

bool ir::replaceAllUsesWith(const Value &value, std::weak_ptr<Value> value2) {
    assert(!value2.expired() && *value2.lock()->type() == *value.type());

    bool changed = false;

    while (!value.use_empty()) {
        value.use_begin()->set(value2);
        changed = true;
    }

    return changed;
}
