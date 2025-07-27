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

#define TARGET_FPS 60

/// @brief The number of frames
unsigned long framesCounter = 0;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");

    // Initialize all required variables and load all required data here!
    ScreenState screen = ScreenState(screenWidth, screenHeight);

    // Set desired framerate (frames-per-second)
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
       // Update
       screen.Update(framesCounter);

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);
            screen.Draw();

        EndDrawing();

        ++framesCounter;
    }

    // Unload all loaded data (textures, fonts, audio) here!

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
