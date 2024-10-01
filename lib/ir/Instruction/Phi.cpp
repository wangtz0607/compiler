#include "ir/Instruction/Phi.h"

#include <algorithm>
#include <cassert>
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

#include "ir/BasicBlock.h"
#include "ir/Use.h"
#include "ir/Value.h"
#include "utils/Memory.h"
#include "utils/StringJoiner.h"

using namespace ir;

Phi::incoming_iterator Phi::findIncoming(const BasicBlock &B) {
    return std::ranges::find_if(incomings(*this), [&B](Incoming incoming) {
        return &*incoming.block == &B;
    });
}

Phi::const_incoming_iterator Phi::findIncoming(const BasicBlock &B) const {
    return std::ranges::find_if(incomings(*this), [&B](ConstIncoming incoming) {
        return &*incoming.block == &B;
    });
}

void Phi::putIncoming(const BasicBlock &B, std::shared_ptr<Value> value) {
    assert(*value->type() == *type());
    if (auto i = findIncoming(B); i != incoming_end()) {
        i->value.set(std::move(value));
    } else {
        incomings_.emplace_back(std::make_unique<Use<BasicBlock>>(this, weaken(const_cast<BasicBlock &>(B))),
                                std::make_unique<Use<Value>>(this, std::move(value)));
    }
}

void Phi::removeIncoming(Phi::const_incoming_iterator i) {
    incomings_.erase(i.base_);
}

std::unordered_set<const UseBase *> Phi::operands() const {
    std::unordered_set<const UseBase *> operands;
    for (ConstIncoming incoming : incomings(*this)) {
        operands.insert(&incoming.block);
        operands.insert(&incoming.value);
    }
    return operands;
}

std::string Phi::format() const {
    StringJoiner formatted(" ");
    formatted.addFormat("{:o} = phi {}", *this, *type());
    if (!incoming_empty()) {
        StringJoiner formattedIncomings(", ");
        for (ConstIncoming incoming : incomings(*this)) {
            formattedIncomings.addFormat("[ {:o}, {:o} ]", *incoming.value, *incoming.block);
        }
        formatted.addFormat("{}", formattedIncomings);
    }
    return formatted.toString();
}

std::unique_ptr<Value> Phi::clone() const {
    std::unique_ptr<Phi> cloned = std::make_unique<Phi>(type());
    for (ConstIncoming incoming : incomings(*this)) {
        cloned->putIncoming(*incoming.block, share(*incoming.value));
    }
    return cloned;
}

bool ir::hasIncomingBlock(const Phi &I, const BasicBlock &B) {
    return I.findIncoming(B) != I.incoming_end();
}

void ir::removeIncomingBlock(Phi &I, const BasicBlock &B) {
    if (auto i = I.findIncoming(B); i != I.incoming_end()) {
        I.removeIncoming(i);
    }
}

const Use<Value> &ir::getIncomingValue(const Phi &I, const BasicBlock &B) {
    assert(hasIncomingBlock(I, B));
    return I.findIncoming(B)->value;
}

Use<Value> &ir::getIncomingValue(Phi &I, const BasicBlock &B) {
    assert(hasIncomingBlock(I, B));
    return I.findIncoming(B)->value;
}

std::unordered_set<BasicBlock *> ir::incomingBlocks(const Phi &I) {
    std::unordered_set<BasicBlock *> incomingBlocks;
    for (Phi::ConstIncoming incoming : incomings(I)) {
        incomingBlocks.insert(&*incoming.block);
    }
    return incomingBlocks;
}

std::unordered_set<Value *> ir::incomingValues(const Phi &I) {
    std::unordered_set<Value *> incomingValues;
    for (Phi::ConstIncoming incoming : incomings(I)) {
        incomingValues.insert(&*incoming.value);
    }
    return incomingValues;
}
