#pragma once

#include <format>
#include <string>
#include <string_view>
#include <utility>

class StringJoiner {
public:
    explicit StringJoiner(std::string_view delimiter)
        : delimiter_(delimiter), first_(true) {}

    StringJoiner(std::string_view delimiter, std::string_view prefix, std::string_view suffix)
        : delimiter_(delimiter), prefix_(prefix), suffix_(suffix), first_(true) {}

    StringJoiner &add(std::string_view element) {
        if (first_) {
            first_ = false;
        } else {
            out_ += delimiter_;
        }
        out_ += element;
        return *this;
    }

    template <typename... Args>
    StringJoiner &addFormat(std::format_string<Args...> fmt, Args &&...args) {
        return add(std::format(std::move(fmt), std::forward<Args>(args)...));
    }

    std::string toString() const {
        return std::string(prefix_) + out_ + std::string(suffix_);
    }

private:
    std::string_view delimiter_, prefix_, suffix_;
    std::string out_;
    bool first_;
};

template <>
struct std::formatter<StringJoiner> {
    constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    auto format(const StringJoiner &joiner, std::format_context &ctx) const {
        return std::format_to(ctx.out(), "{}", joiner.toString());
    }
};
