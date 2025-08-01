#ifndef INCLUDE_GUI_BOARDLIB_H_
#define INCLUDE_GUI_BOARDLIB_H_

#include "raylib.h"

#include "constants/constantslib.hpp"   // constants::EMPTY
#include "node/nodelib.hpp" // Node, GetState()

class Board
{
public:
    Board(int screenWidth, int screenHeight)
    : screenWidth_(screenWidth),
    screenHeight_(screenHeight),
    nodePtr_ (std::make_unique<Node>()),
    numbers_(LoadTexture("resources/numbers.png"))
    {
    }

    ~Board()
    {
        UnloadTexture(numbers_);
    }

    /// @brief Updates the state
    void Update();

    /// @brief Draws the animation on the screen according to the current state
    void Draw() const
    {
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

        const float w = numbers_.width / 5.0f;
        const float h = numbers_.height / 2.0f;
        const float offsetW = cellWidth / 5;
        const float offsetH = cellHeight / 8;
        std::vector<int> curState = nodePtr_->GetState();
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
                float posX = boxX + ((i % 3) * cellWidth) + offsetW;
                float posY = boxY + ((i / 3) * cellHeight) + offsetH;
                Vector2 position = { posX, posY };

                // Draw a fraction of the texture
                DrawTextureRec(numbers_, sourceRec, position, WHITE);
            }
        }
    }

private:
    /// @brief The width of the main screen
    int screenWidth_;

    /// @brief The height of the main screen
    int screenHeight_;

    Texture2D numbers_;

    const int NUM_FRAMES = 3;

    float frameHeight_ = (float)numbers_.height/NUM_FRAMES;
    // Rectangle sourceRec_ = { 0, 0, 200, 200 };

    std::unique_ptr<Node> nodePtr_;
};

#endif // INCLUDE_GUI_BOARDLIB_H_
