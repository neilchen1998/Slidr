#include <iostream> // std::cin
#include <sstream>  // std::cin
#include <string>   // std::string, std::getline
#include <vector>   // std::vector
#include <bitset>   // std::bitset
#include <optional> // std::optional

#include "constants/constantslib.hpp"
#include "terminal/terminallib.hpp"

std::optional<std::vector<int>> try_read_from_terminal_for_8()
{
    bool emptyFound = false;
    std::vector<int> inputState;
    std::string line, s;
    std::getline(std::cin, line);
    std::istringstream iss(line);

    // tries to read the input from the user
    while (iss >> s)
    {
        // if the size is greater than 16
        // the size of the input is invalid
        // if (inputState.size() > constants::FIFTEEN_PUZZLE_SIZE)  return std::nullopt;

        // tries to convert the input value to type int
        // if the input is not integral then cast that to 0xFF
        try
        {
            int value = std::stoi(s);
            if (value > 8 || value < 1) return std::nullopt;
            inputState.emplace_back(value);
        }
        catch(const std::exception& e)
        {
            if (emptyFound == true) return std::nullopt;
            inputState.emplace_back(constants::EMPTY);
            emptyFound = true;
        }
    }

    if (inputState.size() != constants::EIGHT_PUZZLE_NUM) return std::nullopt;

    // makes sure that all values are present
    std::bitset<constants::EIGHT_PUZZLE_NUM> roster;
    roster.reset();
    for (const auto& num : inputState)
    {
        if (num != constants::EMPTY)
        {
            roster.set(num - 1);
        }
        else
        {
            roster.set(constants::EIGHT_PUZZLE_NUM - 1);
        }
    }

    // only return the vector back, iff:
    // 1. the size of the vector is 9
    // 2. all values are present
    // 3. there is an empty piece
    if (inputState.size() == constants::EIGHT_PUZZLE_NUM && roster.all() && emptyFound)
    {
        return inputState;
    }

    return std::nullopt;
}

std::optional<std::vector<int>> try_read_from_terminal_for_15()
{
    bool emptyFound = false;
    std::vector<int> inputState;
    std::string line, s;
    std::getline(std::cin, line);
    std::istringstream iss(line);

    // tries to read the input from the user
    while (iss >> s)
    {
        // if the size is greater than 16
        // the size of the input is invalid
        // if (inputState.size() > constants::FIFTEEN_PUZZLE_SIZE)  return std::nullopt;

        // tries to convert the input value to type int
        // if the input is not integral then cast that to 0xFF
        try
        {
            int value = std::stoi(s);
            if (value > 15 || value < 1) return std::nullopt;
            inputState.emplace_back(value);
        }
        catch(const std::exception& e)
        {
            if (emptyFound == true) return std::nullopt;
            inputState.emplace_back(constants::EMPTY);
            emptyFound = true;
        }
    }

    if (inputState.size() != constants::FIFTEEN_PUZZLE_NUM) return std::nullopt;

    // makes sure that all values are present
    std::bitset<constants::FIFTEEN_PUZZLE_NUM> roster;
    roster.reset();
    for (const auto& num : inputState)
    {
        if (num != constants::EMPTY)
        {
            roster.set(num - 1);
        }
        else
        {
            roster.set(constants::FIFTEEN_PUZZLE_NUM - 1);
        }
    }

    // only return the vector back, iff:
    // 1. the size of the vector is 16
    // 2. all values are present
    // 3. there is an empty piece
    if (inputState.size() == constants::FIFTEEN_PUZZLE_NUM && roster.all() && emptyFound)
    {
        return inputState;
    }

    return std::nullopt;
}
