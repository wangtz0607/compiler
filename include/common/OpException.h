#pragma once

#include <exception>

class OpException : public std::exception {
public:
    constexpr const char *what() const noexcept override {
        return "OpException";
    }
};
