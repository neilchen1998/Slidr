#include "raylib.h"

#include "gui/screenlib.hpp"

void ScreenManager::Update()
{
    ++framesCounter_;
    switch (curState_)
    {
        case GameScreenState::LOGO:
        {
            // Wait for the intro before jumping to TITLE screen
            if (framesCounter_ > 320)
            {
                curState_ = GameScreenState::TITLE;
            }
            break;
        }
        case GameScreenState::TITLE:
        {
            // TODO: Update TITLE screen variables here!

            // Press enter to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER))
            {
                curState_ = GameScreenState::GAMEPLAY;
            }
            break;
        }
        case GameScreenState::GAMEPLAY:
        {
            // TODO: Update GAMEPLAY screen variables here!

            // Press enter to change to ENDING screen
            if (IsKeyPressed(KEY_ENTER))
            {
                curState_ = GameScreenState::ENDING;
            }
            break;
        }
        case GameScreenState::ENDING:
        {
            // TODO: Update ENDING screen variables here!

            // Press enter to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER))
            {
                curState_ = GameScreenState::TITLE;
            }
            break;
        }
        default: break;
    }
}

void ScreenManager::Draw()
{
    switch(curState_)
    {
        case GameScreenState::LOGO:
        {
            DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);

            break;
        }
        case GameScreenState::TITLE:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, GREEN);
            DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
            DrawText("PRESS ENTER to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

            break;
        }
        case GameScreenState::GAMEPLAY:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, PURPLE);
            DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
            DrawText("PRESS ENTER to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

            break;
        }
        case GameScreenState::ENDING:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
            DrawText("PRESS ENTER to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

            break;
        }
        default: break;
    }
}
