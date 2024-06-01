#ifndef INCLUDE_TERMINAL_TERMINALLIB_H_
#define INCLUDE_TERMINAL_TERMINALLIB_H_

#include <vector>   // std::vector
#include <optional> // std::optional

std::optional<std::vector<int>> try_read_from_terminal_for_8();
std::optional<std::vector<int>> try_read_from_terminal_for_15();

#endif // INCLUDE_TERMINAL_TERMINALLIB_H_
