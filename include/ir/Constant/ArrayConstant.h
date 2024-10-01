#pragma once

#include <cstddef>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include "ir/Constant.h"
#include "ir/ConstantVisitor.h"
#include "ir/Type.h"
#include "ir/Type/ArrayType.h"
#include "ir/Use.h"
#include "ir/Value.h"
#include "utils/IndirectIterator.h"

namespace ir {

class ArrayConstant final : public Constant {
    using ElementList = std::vector<std::unique_ptr<Use<Constant>>>;

public:
    using element_iterator = IndirectIterator<ElementList::iterator, Use<Constant>>;
    using const_element_iterator = IndirectIterator<ElementList::const_iterator, const Use<Constant>>;

    ArrayConstant(std::unique_ptr<ArrayType> type, std::vector<std::shared_ptr<Constant>> elements);

    element_iterator element_begin() {
        return element_iterator(elements_.begin());
    }

    element_iterator element_end() {
        return element_iterator(elements_.end());
    }

    const_element_iterator element_begin() const {
        return const_element_iterator(elements_.begin());
    }

    const_element_iterator element_end() const {
        return const_element_iterator(elements_.end());
    }

    bool element_empty() const {
        return elements_.empty();
    }

    size_t element_size() const {
        return elements_.size();
    }

    void accept(ConstantVisitor &visitor) override {
        visitor.visitArrayConstant(*this);
    }

    void accept(ConstantVisitor &visitor) const override {
        visitor.visitArrayConstant(*this);
    }

    std::unique_ptr<Type> type() const override {
        return type_->clone();
    }

    std::string format() const override;
    std::unique_ptr<Value> clone() const override;

protected:
    bool equals(const Constant &other) const override;

private:
    std::unique_ptr<ArrayType> type_;
    ElementList elements_;
};

inline auto elements(ArrayConstant &C) {
    return std::ranges::subrange(C.element_begin(), C.element_end());
}

inline auto elements(const ArrayConstant &C) {
    return std::ranges::subrange(C.element_begin(), C.element_end());
}

std::vector<std::shared_ptr<Constant>> flatten(const Constant &C);

} // namespace ir
