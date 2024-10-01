#include "mc/Fragment.h"

#include <string>

#include "mc/Directive.h"
#include "mc/Instruction.h"
#include "mc/Label.h"
#include "utils/StringJoiner.h"

using namespace mc;

std::string Fragment::format() const {
    StringJoiner formatted("\n");
    if (isGlobal()) {
        formatted.addFormat("  .globl {}", name());
    }
    formatted.addFormat("{}:", name());
    for (const Line &line : *this) {
        if (dynamic_cast<const Instruction *>(&line)) {
            formatted.addFormat("  {}", line);
        }
        if (dynamic_cast<const Directive *>(&line)) {
            formatted.addFormat("  {}", line);
        }
        if (dynamic_cast<const Label *>(&line)) {
            formatted.addFormat("{}", line);
        }
    }
    return formatted.toString();
}
