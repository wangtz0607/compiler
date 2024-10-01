#include "mir/Constant/I8ArrayConstant.h"

#include <string>

#include "utils/StringJoiner.h"

using namespace mir;

std::string I8ArrayConstant::format() const {
    StringJoiner formatted("\n", "i8 [\n", "\n]");
    for (int8_t element : elements()) {
        formatted.addFormat("  {}", element);
    }
    return formatted.toString();
}
