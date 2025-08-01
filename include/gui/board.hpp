#ifndef INCLUDE_GUI_BOARDLIB_H_
#define INCLUDE_GUI_BOARDLIB_H_

#include "raylib.h"

#include "constants/constantslib.hpp"   // constants::EMPTY
#include "node/nodelib.hpp" // Node, GetState()

class Board
{
public:
    /// @brief The constructor of this class
    /// @param screenWidth the width of the screen in pixel
    /// @param screenHeight the height of the screen in pixel
    explicit Board(int screenWidth, int screenHeight);

    ~Board();

    Board() = delete;

    /// @brief Updates the state
    void Update();

    /// @brief Draws the animation on the screen according to the current state
    void Draw() const;

private:
    /// @brief The width of the main screen
    int screenWidth_;

    /// @brief The height of the main screen
    int screenHeight_;

    /// @brief the texture of the board pieces
    Texture2D numbers_;

    /// @brief the pointer that points to the node of the board
    std::unique_ptr<Node> nodePtr_;

    /// @brief the width of the board
    int boardWidth__;

    /// @brief the height of the board
    int boardHeight_;

    /// @brief the thickness of the boarder of the board
    int borderThickness_;

    /// @brief the x position of the board
    float boxX_;

    /// @brief the y position of the board
    float boxY_;

    /// @brief the number of grids in the board
    int N_;

    /// @brief the width of each grid in the board
    float cellWidth_;

    /// @brief the height of each grid in the board
    float cellHeight_;

    /// @brief the width
    float w;

    /// @brief the height
    float h;

    /// @brief the width offset for the puzzle piece image
    float offsetW_;

    /// @brief the height offset for the puzzle piece image
    float offsetH_;
};

#endif // INCLUDE_GUI_BOARDLIB_H_
