#include "mir/Constant/I16ArrayConstant.h"

#include <string>

#include "utils/StringJoiner.h"

using namespace mir;

std::string I16ArrayConstant::format() const {
    StringJoiner formatted("\n", "i16 [\n", "\n]");
    for (int16_t element : elements()) {
        formatted.addFormat("  {}", element);
    }
    return formatted.toString();
}
