#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <vector>    // std::vector
#include <chrono>   // std::chrono::high_resolution_clock, std::chrono::duration_cast
#include <fmt/core.h>   // fmt::print

#include "raylib.h"

#include "gui/screenlib.hpp"

#define TARGET_FPS 60

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 1200;

    InitWindow(screenWidth, screenHeight, "8 Puzzle");

    // Initialize all required variables and load all required data here!
    ScreenManager manager {};

    // Set desired framerate (frames-per-second)
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        fmt::print("Too many arguments!Enter the puzzle pieces without spaces between them.\n");
        return EXIT_FAILURE;
    }

    // Check if an additional input is provided
    // otherwise an example input is used
    std::vector<int> layout;
    if (argc == 2)
    {
        auto res = prompt::parse_string_to_layout(argv[1]);
        if (!res)
        {
            fmt::print("The puzzle should only contains numbers from 1 to 8 and use 'x' or 'X' to denote the empty piece.\n");
            return EXIT_FAILURE;
        }

        layout = std::move(res.value());    // use std::move to avoid the copy
    }
    else
    {
        fmt::print("No additional argument is provided! An example puzzle layout will be used.\n");
        layout = {6, 4, 7, 8, 5, constants::EMPTY, 3, 2, 1};
    }

    auto start = std::chrono::high_resolution_clock::now();
    Solver s = Solver(layout);
    auto [isSolved, totalIters] = s.SolvePuzzle();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    fmt::print("Solved in: {} µs\t# of iterations: {}\tTotal moves: {}\n", duration.count(), totalIters, s.GetNumOfMoves());
    s.PrintPath();

    fmt::print("Moves: {}\n", s.GetSolution());

    return EXIT_SUCCESS;
}
