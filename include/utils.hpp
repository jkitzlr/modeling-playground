#pragma once

#include <string>

/// @brief Returns the minimum of two values
/// @tparam T Any type that supports ordered comparison
/// @param a the left operand
/// @param b the right operand
/// @return the smaller of a and b
template <typename T>
inline T min(T& a, T& b) {
    return a < b ? a : b;
}

/// @brief Create a new lowercase string from the input
/// @param input The string to convert to lower-case
/// @return New string that's all lower-case
inline std::string tolower_new(const std::string& input) {
    std::string lower;
    for (const auto& c : input) {
        lower.push_back(std::tolower(c));
    }
    return lower;
}

/// @brief Convert a string to lowercase in-place
/// @param input The string to convert to lower-case
/// @return Mutated string
inline std::string& tolower(std::string& input) {
    for (auto& c : input) {
        c = std::tolower(c);
    }
    return input;
}
