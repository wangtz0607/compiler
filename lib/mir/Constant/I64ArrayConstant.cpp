#include "mir/Constant/I64ArrayConstant.h"

#include <string>

#include "utils/StringJoiner.h"

using namespace mir;

std::string I64ArrayConstant::format() const {
    StringJoiner formatted("\n", "i64 [\n", "\n]");
    for (int64_t element : elements()) {
        formatted.addFormat("  {}", element);
    }
    return formatted.toString();
}
