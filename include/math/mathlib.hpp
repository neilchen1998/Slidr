#ifndef INCLUDE_MATH_MATHLIB_H_
#define INCLUDE_MATH_MATHLIB_H_

#include <cstdlib>  // std::size_t
#include <span> // std::span
#include <functional>   // std::hash
#include <numeric>   // std::accumulate
#include <concepts> // std::integral

template <std::integral T>
std::size_t hash_range(std::span<T> vec)
{
    // creates a hasher
    std::hash<T> h;

    // iterates through the entire span of the vector, calculates the hash value
    // and returns the value
    return std::accumulate(vec.begin(), vec.end(), vec.size(),
        [&](std::size_t s, T v)
        {
            return s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
        });
}

#endif // INCLUDE_MATH_MATHLIB_H_
