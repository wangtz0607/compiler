#include "mir/Module.h"

#include <memory>
#include <string>
#include <utility>

#include "mir/Function.h"
#include "mir/GlobalVar.h"
#include "utils/StringJoiner.h"

using namespace mir;

GlobalVar &Module::GlobalVars::add(Module::GlobalVars::const_iterator pos, std::unique_ptr<GlobalVar> G) {
    return **globalVars_.insert(pos.base(), std::move(G));
}

std::unique_ptr<GlobalVar> Module::GlobalVars::remove(Module::GlobalVars::const_iterator pos) {
    std::unique_ptr<GlobalVar> G = std::move(const_cast<std::unique_ptr<GlobalVar> &>(*pos.base()));
    globalVars_.erase(pos.base());
    return G;
}

Function &Module::Functions::add(Module::Functions::const_iterator pos, std::unique_ptr<Function> F) {
    return **functions_.insert(pos.base(), std::move(F));
}

std::unique_ptr<Function> Module::Functions::remove(Module::Functions::iterator pos) {
    std::unique_ptr<Function> F = std::move(*pos.base());
    functions_.erase(pos.base());
    return F;
}

std::string Module::format() const {
    StringJoiner formatted("\n\n");
    for (const GlobalVar &G : globalVars) {
        formatted.addFormat("{}", G);
    }
    for (const Function &F : functions) {
        formatted.addFormat("{}", F);
    }
    return formatted.toString();
}
