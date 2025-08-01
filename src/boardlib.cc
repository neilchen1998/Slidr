#include <memory>   // std::make_unique
#include <span>     // std::span

#include "raylib.h" // LoadTexture, Vector2, Rectangle

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
}

Board::~Board()
{
    // Unload texture to prevent memory leaks
    UnloadTexture(numbers_);
}

void Board::Update()
{
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
