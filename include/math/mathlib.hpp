#ifndef INCLUDE_MATH_MATHLIB_H_
#define INCLUDE_MATH_MATHLIB_H_

#include <cstddef>  // std::size_t
#include <span> // std::span
#include <functional>   // std::hash
#include <concepts> // std::integral
// #include <boost/functional/hash.hpp> // if you want to use boost::hash_combine

/// @brief Hashes multiple arguments with an initial hash value using fold expressions
/// @tparam T The first argument type
/// @tparam ...Args The second and the rest argument type
/// @param seed The initial hash value
/// @param u The first argument
/// @param ...v The second and the rest argument
template <std::integral T, std::integral... Args>
inline void hash_combine(std::size_t& seed, const T& u, const Args&... v)
{
    // Hash the first argument
    seed ^= std::hash<T>{}(u) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    // boost::hash_combine(seed, u);

    // Hash the rest of the arguments
    (hash_combine(seed, v), ...);
}

/// @brief Hashes the span
/// @tparam T The type of the element (needs to be integral)
/// @param s The span
/// @return The hash value of the span
template <std::integral T>
inline std::size_t hash_range(std::span<T> s)
{
    // Initialize hash value with the size of the span
    std::size_t h {s.size()};

    // Loop through each element and hash with the element and its position
    for (std::size_t i {0}; i < s.size(); ++i)
    {
        hash_combine(h, s[i], i);
    }

    return h;
}

#endif // INCLUDE_MATH_MATHLIB_H_
