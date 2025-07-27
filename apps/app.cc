#include <stdlib.h> // EXIT_SUCCESS
// #include <vector>    // std::vector
// #include <algorithm>    // std::ranges::equal
// #include <optional> // std::optional
// #include <chrono>   // std::chrono::high_resolution_clock, std::chrono::duration_cast
// #include <random>

#include "raylib.h"
// #include <fmt/core.h>   // fmt::print

// #include "solver/solverlib.hpp" // Solver
// #include "constants/constantslib.hpp"   // constants::EMPTY
#include "gui/screenlib.hpp"
#include "filesystem/saveloadlib.hpp"

#define TARGET_FPS 60

int main(void)
{
    fs::demo();

    return EXIT_SUCCESS;
}
