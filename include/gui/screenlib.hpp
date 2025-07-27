#ifndef INCLUDE_GUI_SCREENLIB_H_
#define INCLUDE_GUI_SCREENLIB_H_

#include "raylib.h"

/// @brief The states of the game
enum struct GameScreen : int
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
};

class ScreenState
{
public:
    ScreenState(int screenWidth, int screenHeight)
        : curState_(GameScreen::LOGO),
        screenWidth_(screenWidth),
        screenHeight_(screenHeight)
    {
    }

    ~ScreenState() = default;

    /// @brief Update the state
    /// @param framesCounter Current frame counter
    void Update(unsigned long framesCounter);

    /// @brief Draw the the state on the screen
    void Draw();

private:
    /// @brief The current state of the game
    GameScreen curState_;

    /// @brief The width of the main screen
    int screenWidth_;

    /// @brief The height of the main screen
    int screenHeight_;
};

#endif // INCLUDE_GUI_SCREENLIB_H_
