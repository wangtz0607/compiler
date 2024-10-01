#pragma once

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <iterator>
#include <list>
#include <memory>
#include <ranges>
#include <string>
#include <unordered_set>
#include <utility>

#include "mir/Instruction.h"
#include "mir/Register.h"
#include "utils/IndirectIterator.h"
#include "utils/Memory.h"

namespace mir {

class BasicBlock {
    using InstructionList = std::list<std::unique_ptr<Instruction>>;

public:
    using iterator = IndirectIterator<InstructionList::iterator, Instruction>;
    using const_iterator = IndirectIterator<InstructionList::const_iterator, const Instruction>;
    using reverse_iterator = IndirectIterator<InstructionList::reverse_iterator, Instruction>;
    using const_reverse_iterator = IndirectIterator<InstructionList::const_reverse_iterator, const Instruction>;

    BasicBlock() = default;
    BasicBlock(const BasicBlock &) = delete;
    BasicBlock(BasicBlock &&) = delete;
    BasicBlock &operator=(const BasicBlock &) = delete;
    BasicBlock &operator=(BasicBlock &&) = delete;

    const std::string &name() const {
        return name_;
    }

    void setName(std::string name) {
        name_ = std::move(name);
    }

    iterator begin() {
        return iterator(insts_.begin());
    }

    const_iterator begin() const {
        return const_iterator(insts_.begin());
    }

    iterator end() {
        return iterator(insts_.end());
    }

    const_iterator end() const {
        return const_iterator(insts_.end());
    }

    reverse_iterator rbegin() {
        return reverse_iterator(insts_.rbegin());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(insts_.rbegin());
    }

    reverse_iterator rend() {
        return reverse_iterator(insts_.rend());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(insts_.rend());
    }

    Instruction &front() {
        return *begin();
    }

    const Instruction &front() const {
        return *begin();
    }

    Instruction &back() {
        return *std::prev(end());
    }

    const Instruction &back() const {
        return *std::prev(end());
    }

    bool empty() const {
        return insts_.empty();
    }

    size_t size() const {
        return insts_.size();
    }

    Instruction &add(const_iterator pos, std::unique_ptr<Instruction> I);

    Instruction &prepend(std::unique_ptr<Instruction> I) {
        return add(begin(), std::move(I));
    }

    Instruction &append(std::unique_ptr<Instruction> I) {
        return add(end(), std::move(I));
    }

    template <typename T>
        requires std::derived_from<T, Instruction>
    T &add(const_iterator pos, std::unique_ptr<T> I) {
        return static_cast<T &>(add(pos, cast<Instruction>(std::move(I))));
    }

    template <typename T>
        requires std::derived_from<T, Instruction>
    T &prepend(std::unique_ptr<T> I) {
        return static_cast<T &>(prepend(cast<Instruction>(std::move(I))));
    }

    template <typename T>
        requires std::derived_from<T, Instruction>
    T &append(std::unique_ptr<T> I) {
        return static_cast<T &>(append(cast<Instruction>(std::move(I))));
    }

    std::unique_ptr<Instruction> remove(const_iterator pos);

    std::unique_ptr<Instruction> removeFirst() {
        return remove(begin());
    }

    std::unique_ptr<Instruction> removeLast() {
        return remove(std::prev(end()));
    }

    void clear() {
        while (!empty()) {
            removeFirst();
        }
    }

    template <typename I>
        requires std::input_iterator<I>
    void assign(I first, I last) {
        clear();
        for (; first != last; ++first) {
            append(std::move(*first));
        }
    }

    template <typename R>
        requires std::ranges::range<R>
    void assign_range(R &&range) {
        assign(range.begin(), range.end());
    }

    std::string format() const;

    std::string formatAsOperand() const {
        return "#" + (!name().empty() ? name() : std::format("{:x}", reinterpret_cast<uintptr_t>(this)));
    }

private:
    std::string name_;
    InstructionList insts_;
};

std::unordered_set<BasicBlock *> successors(const BasicBlock &B);
std::unordered_set<Register *> use(const BasicBlock &B);
std::unordered_set<Register *> def(const BasicBlock &B);

} // namespace mir

template <>
struct std::formatter<mir::BasicBlock> {
    constexpr auto parse(std::format_parse_context &ctx) {
        if (*ctx.begin() == 'o') {
            asOperand_ = true;
            return std::next(ctx.begin());
        }
        return ctx.begin();
    }

    auto format(const mir::BasicBlock &B, std::format_context &ctx) const {
        if (asOperand_) {
            return std::format_to(ctx.out(), "{}", B.formatAsOperand());
        }
        return std::format_to(ctx.out(), "{}", B.format());
    }

private:
    bool asOperand_ = false;
};
