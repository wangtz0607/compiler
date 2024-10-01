#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "ir/BasicBlock.h"
#include "ir/Constant.h"
#include "ir/Function.h"
#include "ir/GlobalVar.h"
#include "ir/Instruction.h"
#include "ir/Module.h"
#include "ir/Type.h"
#include "ir/Value.h"
#include "ir_parser/Symbol.h"
#include "ir_parser/Token.h"

namespace ir {

class ParseException : public std::exception {
public:
    ParseException(std::vector<Token>::const_iterator location, std::string message)
        : location_(location), message_(std::move(message)) {}

    std::vector<Token>::const_iterator location() const {
        return location_;
    }

    const std::string &message() const {
        return message_;
    }

    const char *what() const noexcept override {
        return "ParseException";
    }

private:
    std::vector<Token>::const_iterator location_;
    std::string message_;
};

class Parser {
public:
    explicit Parser(std::vector<Token>::const_iterator cursor) : cursor_(cursor) {}

    Module parseModule();
    std::shared_ptr<GlobalVar> parseGlobalVarHeader(bool &hasInitializer);
    void parseGlobalVarInitializer(GlobalVar &G);
    std::shared_ptr<Function> parseFunctionHeader(bool &hasBody);
    void parseFunctionBody(Function &F);
    void parseBasicBlock(BasicBlock &B);
    std::shared_ptr<Instruction> parseInstruction();
    std::shared_ptr<Value> parseValue(const Type &type);
    std::shared_ptr<Value> parseIdentifier(const Type &type);
    std::unique_ptr<Constant> parseConstant(const Type &type);
    std::unique_ptr<Type> parseType();
    Symbol parseSymbol(std::optional<Symbol::Scope> scope = std::nullopt);

private:
    std::vector<Token>::const_iterator cursor_;
    std::unordered_map<Symbol, std::shared_ptr<Value>> symbolTable_;
};

} // namespace ir
