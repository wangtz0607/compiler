#pragma once

#include <memory>

#include "ir/Function.h"
#include "ir/GlobalVar.h"
#include "ir/Module.h"

namespace ir {

Module parseModule(const char *source);
std::shared_ptr<GlobalVar> parseGlobalVar(const char *source);
std::shared_ptr<Function> parseFunction(const char *source);

} // namespace ir
