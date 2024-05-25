#ifndef INCLUDE_MATH_MATHLIB_H_
#define INCLUDE_MATH_MATHLIB_H_

#include <cstdlib>  // std::size_t
#include <span> // std::span
#include <concepts> // std::integral

template <std::integral T>
std::size_t hash_range(std::span<T> vec)
{
    // uses FNV-1a hash algorithm
    // FNV offset basis: 0xcbf29ce484222325
    // FNV prime: 0x100000001b3
    std::size_t hash = 0xcbf29ce484222325;
    for (const T& v : vec)
    {
        hash ^= v;
        hash *= 0x100000001b3;
    }

    return hash;
}

#endif // INCLUDE_MATH_MATHLIB_H_
