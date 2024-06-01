#ifndef INCLUDE_TERMINAL_TERMINALLIB_H_
#define INCLUDE_TERMINAL_TERMINALLIB_H_

#include <vector>   // std::vector
#include <optional> // std::optional

std::optional<std::vector<int>> parse_string_for_8(const std::string& str);
std::optional<std::vector<int>> parse_string_for_15(const std::string& str);

#endif // INCLUDE_TERMINAL_TERMINALLIB_H_
