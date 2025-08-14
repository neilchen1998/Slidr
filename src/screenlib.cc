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
            if (raylibAnimationPtr_->IsDone())
            {
                curState_ = GameScreenState::TITLE;
            }
            break;
        }
        case GameScreenState::TITLE:
        {
            // Press enter or left click to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                curState_ = GameScreenState::GAMEPLAY;
            }
            break;
        }
        case GameScreenState::GAMEPLAY:
        {
            boardPtr_->Update();

            if (boardPtr_->IsFinished())
            {
                boardPtr_->Reset();
                curState_ = GameScreenState::CELEBRATION;
            }
            else if (boardPtr_->RequestedHelp())
            {
                curState_ = GameScreenState::HELP;
            }

            break;
        }
        case GameScreenState::HELP:
        {
            boardPtr_->UpdateSolution();

            if (boardPtr_->IsFinished())
            {
                curState_ = GameScreenState::SAD;
            }
            break;
        }
        case GameScreenState::CELEBRATION:
        {
            celebrationPtr_->Update();

            // Press enter or left click to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                curState_ = GameScreenState::ENDING;
            }
            break;
        }
        case GameScreenState::SAD:
        {
            // Press enter or left click to change to GAMEPLAY screen
            if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                curState_ = GameScreenState::TITLE;
            }
            break;
        }
        case GameScreenState::ENDING:
        {
            // Press enter to return to TITLE screen
            if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
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
            raylibAnimationPtr_->Draw();

            break;
        }
        case GameScreenState::TITLE:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, JADE_GREEN);

            std::string titleText = "Welcome to 8 Puzzle";
            int titleTextWidth = MeasureText(titleText.c_str(), 60);
            DrawText(titleText.c_str(), (GetScreenWidth() - titleTextWidth) / 2, GetScreenHeight() / 3, 60, BLACK);

            const int subTxtWidth = MeasureText("PRESS ENTER to start", 20);
            DrawText("PRESS ENTER to start", (GetScreenWidth() - subTxtWidth) / 2, 220, 20, DARKBLUE);

            break;
        }
        case GameScreenState::GAMEPLAY:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, BEIGE);

            boardPtr_->Draw();

            break;
        }
        case GameScreenState::HELP:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, RED);

            boardPtr_->DrawSolution();

            break;
        }
        case GameScreenState::CELEBRATION:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, BEIGE);

            const int subTxtWidth = MeasureText("PRESS ENTER to RETURN to TITLE SCREEN", 20);
            DrawText("PRESS ENTER to RETURN to TITLE SCREEN", (GetScreenWidth() - subTxtWidth) / 2, 220 + 150, 20, DARKBLUE);

            boardPtr_->DrawResult();
            celebrationPtr_->Draw();

            break;
        }
        case GameScreenState::SAD:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, RED);

            const int subTxtWidth = MeasureText("PRESS ENTER to RETURN to TITLE SCREEN", 20);
            DrawText("PRESS ENTER to RETURN to TITLE SCREEN", (GetScreenWidth() - subTxtWidth) / 2, 220, 20, DARKBLUE);

            break;
        }
        case GameScreenState::ENDING:
        {
            DrawRectangle(0, 0, screenWidth_, screenHeight_, BLUE);

            const int subTxtWidth = MeasureText("PRESS ENTER to RETURN to TITLE SCREEN", 20);
            DrawText("PRESS ENTER to RETURN to TITLE SCREEN", (GetScreenWidth() - subTxtWidth) / 2, 220, 20, DARKBLUE);

            break;
        }
        default: break;
    }
}
