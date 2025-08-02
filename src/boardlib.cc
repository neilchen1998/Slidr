#include <memory>   // std::make_unique
#include <span>     // std::span
#include <utility>  // std::to_underlying
#include <vector>   // std::vector

#include "raylib.h"     // LoadTexture, Vector2, Rectangle
#include "fmt/core.h"   // fmt::println

#include "gui/board.hpp"

Board::Board(int screenWidth, int screenHeight)
    : screenWidth_(screenWidth),
    screenHeight_(screenHeight),
    nodePtr_ (std::make_unique<Node>()),
    numbers_(LoadTexture("resources/numbers.png")),
    boardWidth__(300),
    boardHeight_(300),
    borderThickness_(10),
    boxX_((screenWidth_ - boardWidth__) / 2),
    boxY_((screenHeight_ - boardHeight_) / 2),
    N_(constants::EIGHT_PUZZLE_SIZE),
    cellWidth_(boardWidth__ / N_),
    cellHeight_(boardHeight_ / N_),
    w(numbers_.width / 5.0f),
    h(numbers_.height / 2.0f),
    offsetW_(cellWidth_ / 5),
    offsetH_(cellHeight_ / 8)
{
    buttonPositions.resize(std::to_underlying(bd::Button::ButtonN));

    // Calculate the position of each piece of the puzzle
    for (size_t i = 0; i < constants::EIGHT_PUZZLE_NUM; i++)
    {
        float posX = boxX_ + ((i % 3) * cellWidth_);
        float posY = boxY_ + ((i / 3) * cellHeight_);
        buttonPositions[i] = Rectangle {posX, posY, cellWidth_, cellHeight_};
    }

    // buttonPositions[std::to_underlying(bd::Button::NewGame)] = Rectangle {, , buttonWidth_, buttonHeight_};
}

Board::~Board()
{
    // Unload texture to prevent memory leaks
    UnloadTexture(numbers_);
}

void Board::Update(const Vector2& mousePoint)
{
    bd::Button btn = CheckWhichButtonIsPressed(mousePoint);

    if ((btn != bd::Button::Invalid) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        std::vector<short> moves = nodePtr_->AvailableMoves();

        int posX = nodePtr_->GetPosX();

        int xRow = posX / constants::EIGHT_PUZZLE_SIZE;
        int xCol = posX % constants::EIGHT_PUZZLE_SIZE;

        int btnRow = std::to_underlying(btn) / constants::EIGHT_PUZZLE_SIZE;
        int btnCol = std::to_underlying(btn) % constants::EIGHT_PUZZLE_SIZE;

        // Check if the condition for moving to the direction is satisfied
        if ((xCol + 1 == btnCol) && (xRow == btnRow))
        {
            nodePtr_->Move(constants::RIGHT);
        }
        else if ((xCol - 1 == btnCol) && (xRow == btnRow))
        {
            nodePtr_->Move(constants::LEFT);
        }
        else if ((xRow + 1 == btnRow) && (xCol == btnCol))
        {
            nodePtr_->Move(constants::DOWN);
        }
        else if ((xRow - 1 == btnRow) && (xCol == btnCol))
        {
            nodePtr_->Move(constants::UP);
        }
    }
}

void Board::Draw() const
{
    // Draw the board
    Rectangle box { boxX_, boxY_, (float)boardWidth__, (float)boardHeight_ };
    DrawRectangleLinesEx(box, borderThickness_, DARKBLUE);

    // Draw the lines
    for (int i = 1; i < N_; i++)
    {
        // Draw horizontal lines
        float y = boxY_ + (i * cellHeight_);
        Vector2 startPos = { boxX_, y };
        Vector2 endPos = { boxX_ + boardWidth__, y };
        DrawLineEx(startPos, endPos, borderThickness_, DARKBLUE);

        // Draw vertical lines
        float x = boxX_ + (i * cellWidth_);
        startPos = { x, boxY_ };
        endPos = { x, boxY_ + boardHeight_ };
        DrawLineEx(startPos, endPos, borderThickness_, DARKBLUE);
    }

    // Loop through all the elements in the node and draw all the pieces
    std::span<const int> curState = nodePtr_->GetState();
    for (size_t i = 0; i < curState.size(); i++)
    {
        // Only draw the number if the current piece is non-empty
        if (int num = curState[i]; num != constants::EMPTY)
        {
            // Calculate the position of the number located on the texture (sprite sheet technique)
            int recX = (num - 1) % 5;
            int recY = (num - 1) / 5;
            Rectangle sourceRec = { recX * w, recY * h, w, h };

            // Calculate the position of the texture
            float posX = boxX_ + ((i % 3) * cellWidth_) + offsetW_;
            float posY = boxY_ + ((i / 3) * cellHeight_) + offsetH_;
            Vector2 position = { posX, posY };

            // Draw a fraction of the texture
            DrawTextureRec(numbers_, sourceRec, position, WHITE);
        }
    }
}

bd::Button Board::CheckWhichButtonIsPressed(const Vector2 &mousePoint)
{
    // Loop through all pieces on the board
    for (size_t i = 0; i < constants::EIGHT_PUZZLE_NUM; i++)
    {
        if (CheckCollisionPointRec(mousePoint, buttonPositions[i]))
        {
            return (bd::Button)i;
        }
    }

    // Not button is pressed
    return bd::Button::Invalid;
}
