#ifndef INCLUDE_MATH_MATHLIB_H_
#define INCLUDE_MATH_MATHLIB_H_

#include <cstdlib>  // std::size_t
#include <span> // std::span
#include <numeric>   // std::accumulate, std::reduce
#include <concepts> // std::integral

template <std::integral T>
std::size_t hash_range(std::span<T> vec)
{
    // iterates through the entire span of the vector, calculates the hash value
    // and returns the value
    return std::reduce(vec.begin(), vec.end(), vec.size(),  // std::reduce in theory runs faster than std::accumulate
        [&](std::size_t s, T v)
        {
            return s ^= v + 0x9e3779b9 + (s << 6) + (s >> 2);
        });
}

#endif // INCLUDE_MATH_MATHLIB_H_
