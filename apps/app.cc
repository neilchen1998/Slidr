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

#define TARGET_FPS 60

enum struct GameScreen : id_t
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
};

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic screen manager");

    GameScreen currentScreen = GameScreen::LOGO;

    // TODO: Initialize all required variables and load all required data here!

    int framesCounter = 0;          // Useful to count frames

    // Set desired framerate (frames-per-second)
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        switch (currentScreen)
        {
            case GameScreen::LOGO:
            {
                // TODO: Update LOGO screen variables here!
                framesCounter++;    // Count frames

                // Wait for 2 seconds (120 frames) before jumping to TITLE screen
                if (framesCounter > 120)
                {
                    currentScreen = GameScreen::TITLE;
                }
                break;
            }
            case GameScreen::TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GameScreen::GAMEPLAY;
                }
                break;
            }
            case GameScreen::GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!

                // Press enter to change to ENDING screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GameScreen::ENDING;
                }
                break;
            }
            case GameScreen::ENDING:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GameScreen::TITLE;
                }
                break;
            }
            default: break;
        }

        // Draw
        BeginDrawing();

            ClearBackground(RAYWHITE);

            switch(currentScreen)
            {
                case GameScreen::LOGO:
                {
                    // TODO: Draw LOGO screen here!
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

                    break;
                }
                case GameScreen::TITLE:
                {
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

                    break;
                }
                case GameScreen::GAMEPLAY:
                {
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
                    DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
                    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

                    break;
                }
                case GameScreen::ENDING:
                {
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

                    break;
                }
                default: break;
            }

        EndDrawing();
    }

    // TODO: Unload all loaded data (textures, fonts, audio) here!

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
