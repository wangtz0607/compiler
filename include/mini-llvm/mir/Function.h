#pragma once

#include <cassert>
#include <cstddef>
#include <format>
#include <iterator>
#include <list>
#include <memory>
#include <string>
#include <utility>

#include "mini-llvm/common/Linkage.h"
#include "mini-llvm/mir/BasicBlock.h"
#include "mini-llvm/mir/StackFrame.h"
#include "mini-llvm/utils/IndirectIterator.h"

namespace mini_llvm::mir {

class Function {
    using BasicBlockList = std::list<std::unique_ptr<BasicBlock>>;

public:
    using iterator = IndirectIterator<BasicBlockList::iterator, BasicBlock>;
    using const_iterator = IndirectIterator<BasicBlockList::const_iterator, const BasicBlock>;
    using reverse_iterator = IndirectIterator<BasicBlockList::reverse_iterator, BasicBlock>;
    using const_reverse_iterator = IndirectIterator<BasicBlockList::const_reverse_iterator, const BasicBlock>;

    explicit Function(std::string name, Linkage linkage) : name_(std::move(name)), linkage_(linkage) {}

    Function(const Function &) = delete;
    Function(Function &&) = delete;
    Function &operator=(const Function &&) = delete;
    Function &operator=(Function &&) = delete;

    const std::string &name() const {
        return name_;
    }

    Linkage linkage() const {
        return linkage_;
    }

    iterator begin() {
        return iterator(blocks_.begin());
    }

    const_iterator begin() const {
        return const_iterator(blocks_.begin());
    }

    iterator end() {
        return iterator(blocks_.end());
    }

    const_iterator end() const {
        return const_iterator(blocks_.end());
    }

    reverse_iterator rbegin() {
        return reverse_iterator(blocks_.rbegin());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(blocks_.rbegin());
    }

    reverse_iterator rend() {
        return reverse_iterator(blocks_.rend());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(blocks_.rend());
    }

    BasicBlock &front() {
        return *begin();
    }

    const BasicBlock &front() const {
        return *begin();
    }

    BasicBlock &back() {
        return *std::prev(end());
    }

    const BasicBlock &back() const {
        return *std::prev(end());
    }

    bool empty() const {
        return blocks_.empty();
    }

    size_t size() const {
        return blocks_.size();
    }

    BasicBlock &entry() {
        return front();
    }

    const BasicBlock &entry() const {
        return front();
    }

    BasicBlock &add(const_iterator pos, std::unique_ptr<BasicBlock> block);

    BasicBlock &add(const_iterator pos) {
        return add(pos, std::make_unique<BasicBlock>());
    }

    BasicBlock &prepend(std::unique_ptr<BasicBlock> block) {
        return add(begin(), std::move(block));
    }

    BasicBlock &prepend() {
        return prepend(std::make_unique<BasicBlock>());
    }

    BasicBlock &append(std::unique_ptr<BasicBlock> block) {
        return add(end(), std::move(block));
    }

    BasicBlock &append() {
        return append(std::make_unique<BasicBlock>());
    }

    std::unique_ptr<BasicBlock> remove(const_iterator pos);

    std::unique_ptr<BasicBlock> removeFirst() {
        return remove(begin());
    }

    std::unique_ptr<BasicBlock> removeLast() {
        return remove(std::prev(end()));
    }

    void clear() {
        while (!empty()) {
            removeFirst();
        }
    }

    StackFrame &stackFrame() {
        return stackFrame_;
    }

    const StackFrame &stackFrame() const {
        return stackFrame_;
    }

    std::string format() const;

    std::string formatAsOperand() const {
        return "@" + name();
    }

private:
    std::string name_;
    Linkage linkage_;
    BasicBlockList blocks_;
    StackFrame stackFrame_;
};

} // namespace mini_llvm::mir

template <>
struct std::formatter<mini_llvm::mir::Function> {
    constexpr auto parse(std::format_parse_context &ctx) {
        if (*ctx.begin() == 'o') {
            asOperand_ = true;
            return std::next(ctx.begin());
        }
        return ctx.begin();
    }

    auto format(const mini_llvm::mir::Function &F, std::format_context &ctx) const {
        if (asOperand_) {
            return std::format_to(ctx.out(), "{}", F.formatAsOperand());
        }
        return std::format_to(ctx.out(), "{}", F.format());
    }

private:
    bool asOperand_ = false;
};
