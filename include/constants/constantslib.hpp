#ifndef INCLUDE_CONSTANTS_CONSTANTSLIB_H_
#define INCLUDE_CONSTANTS_CONSTANTSLIB_H_

// source: https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/

namespace constants
{
    /// @brief the empty piece
    inline constexpr int EMPTY { 0xFF };

    /// @brief the grid size of the 8 puzzle problem
    inline constexpr int EIGHT_PUZZLE_SIZE { 3 };

    /// @brief the grid size of the 8 puzzle problem
    inline constexpr int FIFTEEN_PUZZLE_SIZE { 4 };

    /// @brief the total number of pieces of 8 puzzle problem
    inline constexpr int EIGHT_PUZZLE_NUM { (EIGHT_PUZZLE_SIZE * EIGHT_PUZZLE_SIZE) };

    /// @brief the total number of pieces of 8 puzzle problem
    inline constexpr int FIFTEEN_PUZZLE_NUM { (FIFTEEN_PUZZLE_SIZE * FIFTEEN_PUZZLE_SIZE) };

    /// @brief the right direction
    inline constexpr int RIGHT { 0 };

    /// @brief the up direction
    inline constexpr int UP   { 1 };

    /// @brief the left direction
    inline constexpr int LEFT  { 2 };

    /// @brief the down direction
    inline constexpr int DOWN  { 3 };
} // namespace constants

#endif // INCLUDE_CONSTANTS_CONSTANTSLIB_H_
