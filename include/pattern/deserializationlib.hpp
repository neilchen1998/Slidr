#ifndef INCLUDE_PATTERN_DESERIALIZATIONLIB_H_
#define INCLUDE_PATTERN_DESERIALIZATIONLIB_H_

#include <vector>   // std::vector
#include <string>   // std::string
#include <sstream>  // std::istringstream

namespace pattern
{
    /// @brief Deserialize a string to its original data
    /// @param data the encoded string
    /// @return the original vector
    std::vector<int> deserialize(const std::string& data)
    {
        std::vector<int> ret;

        // grabs two characters from the string at a time
        // and converts them from hex to decimal
        for (size_t i = 0; i < data.length(); i += 2)
        {
            int val;
            std::istringstream(data.substr(i, 2)) >> std::hex >> val;
            ret.emplace_back(val);
        }
        
        return ret;
    }
}   // namespace pattern

#endif // INCLUDE_PATTERN_DESERIALIZATIONLIB_H_
