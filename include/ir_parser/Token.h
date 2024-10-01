#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace ir {

struct Token {
    enum class Kind {
#define X(enumerator) k##enumerator,
#include "ir_parser/TokenKind.def"
#undef X
    };

    Kind kind;
    std::variant<std::monostate, int64_t, std::string, std::vector<int8_t>> value;
    const char *location;
};

inline bool operator==(const Token &lhs, const Token &rhs) {
    return lhs.kind == rhs.kind && rhs.value == rhs.value && lhs.location == rhs.location;
}

inline constexpr const char *name(Token::Kind kind) {
    switch (kind) {
#define X(enumerator) case Token::Kind::k##enumerator: return #enumerator;
#include "ir_parser/TokenKind.def"
#undef X
    default:
        std::unreachable();
    }
}

} // namespace ir
