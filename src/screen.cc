#include "raylib.h"

#include "gui/screen.hpp"

void ScreenState::Update(unsigned long framesCounter)
{
    switch (curState_)
    {
        case GameScreen::LOGO:
        {
            // Wait for 2 seconds (120 frames) before jumping to TITLE screen
            if (framesCounter > 90)
            {
                curState_ = GameScreen::TITLE;
            }
            break;
        }
        case GameScreen::TITLE:
        {
            // TODO: Update TITLE screen variables here!

            // Press enter to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER))
            {
                curState_ = GameScreen::GAMEPLAY;
            }
            break;
        }
        case GameScreen::GAMEPLAY:
        {
            // TODO: Update GAMEPLAY screen variables here!

            // Press enter to change to ENDING screen
            if (IsKeyPressed(KEY_ENTER))
            {
                curState_ = GameScreen::ENDING;
            }
            break;
        }
        case GameScreen::ENDING:
        {
            // TODO: Update ENDING screen variables here!

            // Press enter to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER))
            {
                curState_ = GameScreen::TITLE;
            }
            break;
        }
        default: break;
    }
}

void ScreenState::Draw()
{
    switch(curState_)
    {
        case GameScreen::LOGO:
        {
            DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
            DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

            break;
        }
        case GameScreen::TITLE:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, GREEN);
            DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

            break;
        }
        case GameScreen::GAMEPLAY:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, PURPLE);
            DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
            DrawText("PRESS ENTER to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

            break;
        }
        case GameScreen::ENDING:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

            break;
        }
        default: break;
    }
}
