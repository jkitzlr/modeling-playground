#pragma once

/// @brief Returns the minimum of two values
/// @tparam T Any type that supports ordered comparison
/// @param a the left operand
/// @param b the right operand
/// @return the smaller of a and b
template <typename T>
inline T min(T& a, T& b) {
    return a < b ? a : b;
}
