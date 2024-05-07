#ifndef INCLUDE_PATTERN_PATTERNLIB_H_
#define INCLUDE_PATTERN_PATTERNLIB_H_

#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <string>   // std::string
#include <sstream>  // std::ostringstream
#include <utility>  // std::pair
#include <unordered_map>  // std::unordered_map

namespace pattern
{
    /// @brief Export the solution of a state
    /// @param hash the state (in hash code)
    /// @param vec the solution
    /// @param filename the export file name
    /// @param append whether to append the exsiting file
    void ExportSolution(std::size_t hash, std::vector<int>& vec, const std::string& filename, bool append = true);

    /// @brief Load solutions 
    /// @param filename the name of the file
    /// @return the solutions {hash, solution}
    std::unordered_map<std::size_t, std::vector<int>> LoadSolution(const std::string& filename);
}   // namespace pattern

#endif // INCLUDE_PATTERN_PATTERNLIB_H_
