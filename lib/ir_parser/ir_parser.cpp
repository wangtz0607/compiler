#include "ir_parser/ir_parser.h"

#include <memory>
#include <vector>

#include "ir/Function.h"
#include "ir/GlobalVar.h"
#include "ir/Module.h"
#include "ir_parser/Lexer.h"
#include "ir_parser/Parser.h"
#include "ir_parser/Token.h"
#include "utils/Memory.h"

using namespace ir;

Module ir::parseModule(const char *source) {
    return Parser(std::vector<Token>(Lexer(source)).begin()).parseModule();
}

std::shared_ptr<GlobalVar> ir::parseGlobalVar(const char *source) {
    Module M = parseModule(source);
    return share(M.globalVars.front());
}

std::shared_ptr<Function> ir::parseFunction(const char *source) {
    Module M = parseModule(source);
    return share(M.functions.front());
}
