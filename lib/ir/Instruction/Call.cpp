#include "ir/Instruction/Call.h"

#include <memory>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "ir/Function.h"
#include "ir/Type/Void.h"
#include "ir/Use.h"
#include "ir/Value.h"
#include "utils/Memory.h"
#include "utils/StringJoiner.h"

using namespace ir;

Call::Call(std::weak_ptr<Function> callee, std::vector<std::shared_ptr<Value>> args)
        : callee_(this, std::move(callee)) {
    for (auto &arg : args) {
        args_.push_back(std::make_unique<Use<Value>>(this, std::move(arg)));
    }
}

std::unordered_set<const UseBase *> Call::operands() const {
    std::unordered_set<const UseBase *> operands;
    operands.insert(&callee());
    for (const UseBase &arg : args(*this)) {
        operands.insert(&arg);
    }
    return operands;
}

std::string Call::format() const {
    StringJoiner formattedArgs(", ");
    for (const Use<Value> &arg : args(*this)) {
        formattedArgs.addFormat("{} {:o}", *arg->type(), *arg);
    }
    StringJoiner formatted(" ");
    if (*type() != Void()) {
        formatted.addFormat("{:o} =", *this);
    }
    formatted.add("call");
    formatted.addFormat("{}", *type());
    formatted.addFormat("{:o}({})", *callee(), formattedArgs);
    return formatted.toString();
}

std::unique_ptr<Value> Call::clone() const {
    std::vector<std::shared_ptr<Value>> clonedArgs;
    for (const Use<Value> &arg : args(*this)) {
        clonedArgs.push_back(share(*arg));
    }
    return std::make_unique<Call>(share(*callee()), std::move(clonedArgs));
}
