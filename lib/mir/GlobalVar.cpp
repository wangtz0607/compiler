#include "mir/GlobalVar.h"

#include <format>
#include <string>

#include "utils/StringJoiner.h"

using namespace mir;

std::string GlobalVar::format() const {
    if (!hasInitializer()) {
        return std::format("undef {:o}", *this);
    }
    StringJoiner formatted(" ");
    if (linkage() == Linkage::kInternal) {
        formatted.add("internal");
    }
    formatted.addFormat("{:o}: {}", *this, initializer());
    return formatted.toString();
}
