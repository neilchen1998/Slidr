#ifndef INCLUDE_MATH_MATHLIB_H_
#define INCLUDE_MATH_MATHLIB_H_

#include <cstdlib>  // std::size_t
#include <span> // std::span
#include <functional>   // std::hash
#include <numeric>   // std::accumulate, std::reduce
#include <concepts> // std::integral

/// @brief Hashes multiple arguments with an initial hash value using fold expressions
/// @tparam T The first argument type
/// @tparam ...Args The second and the rest argument type
/// @param seed The initial hash value
/// @param u The first argument
/// @param ...v The second and the rest argument
template <std::integral T, std::integral ... Args>
inline void hash_combine(std::size_t& seed, const T& u, const Args&... v)
{
    // Hash the first argument
    seed ^= std::hash<T>{}(u) + 0x9e3779b9 + (seed << 6) + (seed >> 2);

    // Hash the rest of the arguments
    (hash_combine(seed, v), ...);
}

template <std::integral T>
inline std::size_t hash_range(std::span<T> vec)
{
    std::size_t h {vec.size()};
    for (std::size_t i {0}; i < vec.size(); ++i)
    {
        hash_combine(h, vec[i], i);
    }

    return h;
}

#endif // INCLUDE_MATH_MATHLIB_H_
