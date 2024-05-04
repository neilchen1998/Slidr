#ifndef INCLUDE_PATTERN_SERIALIZATIONLIB_H_
#define INCLUDE_PATTERN_SERIALIZATIONLIB_H_

#include <vector>   // std::vector
#include <string>   // std::string
#include <sstream>  // std::ostringstream
#include <iomanip>  // std::setfill, std::setw

#include "constants/constantslib.hpp"

typedef unsigned long uint64_t;

namespace pattern
{
    template <typename T>
    std::string serialize(const std::vector<T>& vec)
    {
        std::ostringstream oss;
        for (const auto& v : vec)
        {
            oss << std::setfill('0') <<  std::setw(2) << std::hex << v;
        }

        return oss.str();
    }
}   // namespace pattern

#endif // INCLUDE_PATTERN_SERIALIZATIONLIB_H_
