#ifndef INCLUDE_PATTERN_SERIALIZATIONLIB_H_
#define INCLUDE_PATTERN_SERIALIZATIONLIB_H_

#include <vector>   // std::vector
#include <string>   // std::string
#include <sstream>  // std::ostringstream
#include <iomanip>  // std::setfill, std::setw
#include <concepts> // std::integral

#include "constants/constantslib.hpp"

namespace pattern
{
    /// @brief Serialize a vector of integers to string form (in hex)
    /// @tparam T the data type (has to be integral)
    /// @param vec the input vector
    /// @return a string
    template <std::integral T>
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
