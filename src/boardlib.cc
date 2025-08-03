#include <memory>   // std::make_unique
#include <span>     // std::span
#include <utility>  // std::to_underlying
#include <vector>   // std::vector

#include "raylib.h"     // LoadTexture, Vector2, Rectangle
#include "fmt/core.h"   // fmt::println

#include "gui/board.hpp"

#define CRIMSON    CLITERAL(Color){ 210, 31, 60, 255 }       // Crimson
#define FIREBRICK  CLITERAL(Color){ 178, 34, 34, 255 }       // Fire Brick
#define TIGER      CLITERAL(Color){ 249, 104, 21, 255 }      // Tiger
#define TANGERINE  CLITERAL(Color){ 247, 135, 2, 255 }       // Tangerine
#define APRICOT    CLITERAL(Color){ 237, 130, 14, 255 }      // Apricot

Board::Board(int screenWidth, int screenHeight)
    : screenWidth_(screenWidth),
    screenHeight_(screenHeight),
    numbers_(LoadTexture("resources/numbers.png")),
    boardWidth__(500),
    boardHeight_(500),
    borderThickness_(10),
    boxX_((screenWidth_ - boardWidth__) / 2),
    boxY_((screenHeight_ - boardHeight_) / 2),
    buttonWidth_(200),
    buttonHeight_(80),
    undoBtnX_((screenHeight_ + boardHeight_) / 2 + 10),
    undoBtnY_((screenHeight_ - boardHeight_) / 2),
    restartBtnX_((screenHeight_ + boardHeight_) / 2 + 10),
    restartBtnY_(undoBtnY_ + buttonHeight_ + 10),
    N_(constants::EIGHT_PUZZLE_SIZE),
    cellWidth_(boardWidth__ / N_),
    cellHeight_(boardHeight_ / N_),
    w(numbers_.width / 5.0f),
    h(numbers_.height / 2.0f),
    offsetW_(cellWidth_ / 5),
    offsetH_(cellHeight_ / 8),
    restartBtnState_(bd::ButtonState::Unselected),
    undoBtnState_(bd::ButtonState::Unselected)
{
    buttonPositions_.resize(std::to_underlying(bd::Button::ButtonN));

    // Calculate the position of each piece of the puzzle
    for (size_t i = 0; i < constants::EIGHT_PUZZLE_NUM; i++)
    {
        float posX = boxX_ + ((i % 3) * cellWidth_);
        float posY = boxY_ + ((i / 3) * cellHeight_);
        buttonPositions_[i] = Rectangle {posX, posY, cellWidth_, cellHeight_};
    }

    buttonPositions_[std::to_underlying(bd::Button::Undo)] = Rectangle {undoBtnX_, undoBtnY_, buttonWidth_, buttonHeight_};
    buttonPositions_[std::to_underlying(bd::Button::Restart)] = Rectangle {restartBtnX_, restartBtnY_, buttonWidth_, buttonHeight_};

    std::vector<int> initalLayout {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
    std::shared_ptr<Node> startNode = std::make_shared<Node>(initalLayout);

    history_.push(startNode);
}

Board::~Board()
{
    // Unload texture to prevent memory leaks
    UnloadTexture(numbers_);
}

void Board::Update(const Vector2& mousePoint)
{
    bd::Button btn = CheckWhichButtonIsPressed(mousePoint);

    restartBtnAction_ = false;
    undoBtnAction_ = false;

    if (CheckCollisionPointRec(mousePoint, buttonPositions_[std::to_underlying(bd::Button::Restart)]))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            restartBtnState_ = bd::ButtonState::Selected;
        }
        else
        {
            restartBtnState_ = bd::ButtonState::Hovered;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            restartBtnAction_ = true;
        }
    }
    else
    {
        restartBtnState_ = bd::ButtonState::Unselected;
    }

    if (CheckCollisionPointRec(mousePoint, buttonPositions_[std::to_underlying(bd::Button::Undo)]))
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            undoBtnState_ = bd::ButtonState::Selected;
        }
        else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
        {
            undoBtnAction_ = true;
        }
        else
        {
            undoBtnState_ = bd::ButtonState::Hovered;
        }
    }
    else
    {
        undoBtnState_ = bd::ButtonState::Unselected;
    }

    // Check if the button is clicked
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        switch (btn)
        {
        case bd::Button::PieceOne:
        case bd::Button::PieceTwo:
        case bd::Button::PieceThree:
        case bd::Button::PieceFour:
        case bd::Button::PieceFive:
        case bd::Button::PieceSix:
        case bd::Button::PieceSeven:
        case bd::Button::PieceEight:
        case bd::Button::PieceNine:
        {
            const std::shared_ptr<Node> top = history_.top();

            // Get the position of the empty piece
            int posX = top->GetPosX();
            int xRow = posX / constants::EIGHT_PUZZLE_SIZE;
            int xCol = posX % constants::EIGHT_PUZZLE_SIZE;

            // Get the position of the piece that is clicked
            int btnRow = std::to_underlying(btn) / constants::EIGHT_PUZZLE_SIZE;
            int btnCol = std::to_underlying(btn) % constants::EIGHT_PUZZLE_SIZE;

            // Check if the condition for moving to the direction is satisfied
            if (((xCol + 1) == btnCol) && (xRow == btnRow))
            {
                auto [childLayout, childPosX] = top->GetNextLayout(constants::RIGHT);
                history_.push(std::make_shared<Node>(childLayout, childPosX, top->GetDepth() + 1, top, constants::RIGHT));
            }
            else if (((xCol - 1) == btnCol) && (xRow == btnRow))
            {
                auto [childLayout, childPosX] = top->GetNextLayout(constants::LEFT);
                history_.push(std::make_shared<Node>(childLayout, childPosX, top->GetDepth() + 1, top, constants::LEFT));
            }
            else if (((xRow + 1) == btnRow) && (xCol == btnCol))
            {
                auto [childLayout, childPosX] = top->GetNextLayout(constants::DOWN);
                history_.push(std::make_shared<Node>(childLayout, childPosX, top->GetDepth() + 1, top, constants::DOWN));
            }
            else if (((xRow - 1) == btnRow) && (xCol == btnCol))
            {
                auto [childLayout, childPosX] = top->GetNextLayout(constants::UP);
                history_.push(std::make_shared<Node>(childLayout, childPosX, top->GetDepth() + 1, top, constants::UP));
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }

    if (restartBtnAction_)
    {
        // Pop the stack until there is only one element in the stack
        while (history_.size() > 1)
        {
            history_.pop();
        }
    }

    if (undoBtnAction_)
    {
        // Pop the stack (history) iff there are more than one element in the stack
        if (history_.size() > 1)
        {
            history_.pop();
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
    std::span<const int> curState = history_.top()->GetState();
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

    // Draw text on the buttons
    Rectangle undoBox { undoBtnX_, undoBtnY_, buttonWidth_, buttonHeight_ };
    if (undoBtnState_ == bd::ButtonState::Selected)
    {
        DrawRectangle(undoBox.x, undoBox.y, undoBox.width, undoBox.height, TANGERINE);
        DrawText(TextFormat("Undo"), undoBtnX_ + 15, undoBtnY_ + 15, 40, WHITE);
    }
    else if (undoBtnState_ == bd::ButtonState::Hovered)
    {
        DrawRectangle(undoBox.x, undoBox.y, undoBox.width, undoBox.height, TIGER);
        DrawText(TextFormat("Undo"), undoBtnX_ + 15, undoBtnY_ + 15, 40, WHITE);
    }
    else
    {
        DrawRectangle(undoBox.x, undoBox.y, undoBox.width, undoBox.height, APRICOT);
        DrawText(TextFormat("Undo"), undoBtnX_ + 15, undoBtnY_ + 15, 40, WHITE);
    }

    Rectangle restartBox { restartBtnX_, restartBtnY_, buttonWidth_, buttonHeight_ };
    if (restartBtnState_ == bd::ButtonState::Selected)
    {
        DrawRectangle(restartBox.x, restartBox.y, restartBox.width, restartBox.height, CRIMSON);
        DrawText(TextFormat("Restart"), restartBtnX_ + 15, restartBtnY_ + 15, 40, WHITE);
    }
    else if (restartBtnState_ == bd::ButtonState::Hovered)
    {
        DrawRectangle(restartBox.x, restartBox.y, restartBox.width, restartBox.height, FIREBRICK);
        DrawText(TextFormat("Restart"), restartBtnX_ + 15, restartBtnY_ + 15, 40, WHITE);
    }
    else
    {
        DrawRectangle(restartBox.x, restartBox.y, restartBox.width, restartBox.height, MAROON);
        DrawText(TextFormat("Restart"), restartBtnX_ + 15, restartBtnY_ + 15, 40, WHITE);
    }

    // Draw text on the top
    DrawText(TextFormat("Moves: %02i", history_.top()->GetDepth()), (screenWidth_ - boardWidth__) / 2, (screenHeight_ - boardHeight_) / 2 - 40, 40, BLUE);
}

bd::Button Board::CheckWhichButtonIsPressed(const Vector2 &mousePoint)
{
    // Loop through all pieces on the board
    for (size_t i = 0; i <= std::to_underlying(bd::Button::PieceNine); i++)
    {
        if (CheckCollisionPointRec(mousePoint, buttonPositions_[i]))
        {
            return (bd::Button)i;
        }
    }

    // Not button is pressed
    return bd::Button::Invalid;
}
