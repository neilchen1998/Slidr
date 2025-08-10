#include "raylib.h"

#include "gui/screenlib.hpp"
#include "gui/animationlib.hpp"
#include "gui/colourlib.hpp"

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
            boardPtr_->Update(GetMousePosition());

            // Press enter to change to ENDING screen
            if (boardPtr_->IsFinished())
            {
                boardPtr_->Reset();
                curState_ = GameScreenState::ENDING;
            }
            break;
        }
        case GameScreenState::ENDING:
        {
            celebrationPtr_->Update();

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

            std::string titleText = "Welcome to 8 Puzzle";
            int titleTextWidth = MeasureText(titleText.c_str(), 60);
            DrawText(titleText.c_str(), (GetScreenWidth() - titleTextWidth) / 2, GetScreenHeight() / 3, 60, BLACK);

            break;
        }
        case GameScreenState::GAMEPLAY:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, BEIGE);
            DrawText("GAMEPLAY SCREEN", 20, 20, 20, MAROON);

            boardPtr_->Draw();

            break;
        }
        case GameScreenState::ENDING:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, BLUE);
            DrawText("ENDING SCREEN", 20, 20, 20, DARKBLUE);
            DrawText("PRESS ENTER to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
            celebrationPtr_->Draw();

            break;
        }
        default: break;
    }
}
