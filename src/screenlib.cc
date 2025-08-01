#include "raylib.h"

#include "gui/screenlib.hpp"
#include "gui/animationlib.hpp"

void ScreenManager::Update()
{
    switch (curState_)
    {
        case GameScreenState::LOGO:
        {
            raylibAnimationPtr_->Update();

            // Wait for the intro before jumping to TITLE screen
            // if (raylibAnimationPtr_->IsDone())
            if (true)
            {
                curState_ = GameScreenState::TITLE;
            }
            break;
        }
        case GameScreenState::TITLE:
        {
            // TODO: Update TITLE screen variables here!

            // Press enter to change to GAMEPLAY screen
            // if (IsKeyPressed(KEY_ENTER))
            if (true)
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

void ScreenManager::Draw() const
{
    switch(curState_)
    {
        case GameScreenState::LOGO:
        {
            DrawText("LOGO SCREEN", 20, 20, 20, LIGHTGRAY);

            raylibAnimationPtr_->Draw();

            break;
        }
        case GameScreenState::TITLE:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, GREEN);
            DrawText("TITLE SCREEN", 20, 20, 20, DARKGREEN);
            DrawText("PRESS ENTER to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);

            break;
        }
        case GameScreenState::GAMEPLAY:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, PURPLE);
            DrawText("GAMEPLAY SCREEN", 20, 20, 20, MAROON);

            const int boxWidth = 300;
            const int boxHeight = 300;
            const int borderThickness = 10;
            const float boxX = (screenWidth_ - boxWidth) / 2;
            const float boxY = (screenHeight_ - boxHeight) / 2;

            constexpr int gridSize = 3;
            constexpr float cellWidth = boxWidth / gridSize;
            constexpr float cellHeight = boxHeight / gridSize;

            Rectangle box { boxX, boxY, boxWidth, boxHeight };

            DrawRectangleLinesEx(box, borderThickness, DARKBLUE);

            for (int i = 1; i < gridSize; i++)
            {
                // Draw horizontal lines
                float y = boxY + (i * cellHeight);
                Vector2 startPos = { boxX, y };
                Vector2 endPos = { boxX + boxWidth, y };
                DrawLineEx(startPos, endPos, borderThickness, DARKBLUE);

                // Draw vertical lines
                float x = boxX + (i * cellWidth);
                startPos = { x, boxY };
                endPos = { x, boxY + boxHeight };
                DrawLineEx(startPos, endPos, borderThickness, DARKBLUE);
            }

            break;
        }
        case GameScreenState::ENDING:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 20, DARKBLUE);
            DrawText("PRESS ENTER to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

            break;
        }
        default: break;
    }
}
