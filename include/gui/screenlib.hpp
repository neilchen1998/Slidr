#ifndef INCLUDE_GUI_SCREENLIB_H_
#define INCLUDE_GUI_SCREENLIB_H_

#include <memory>   // std::unique_ptr, std::make_unique
#include "gui/animationlib.hpp"

/// @brief The states of the game
enum struct GameScreenState : int
{
    LOGO = 0,
    TITLE,
    GAMEPLAY,
    ENDING
};

class ScreenManager
{
public:
    ScreenManager(int screenWidth, int screenHeight)
        : curState_(GameScreenState::LOGO),
        screenWidth_(screenWidth),
        screenHeight_(screenHeight),
        raylibAnimationPtr_(std::make_unique<RaylibAnimation>(screenWidth_, screenHeight_))
    {
    }

    ~ScreenManager() = default;

    /// @brief Update the state
    void Update();

    /// @brief Draw the the state on the screen
    void Draw() const;

private:
    /// @brief The current state of the game
    GameScreenState curState_;

    /// @brief The width of the main screen
    int screenWidth_;

    /// @brief The height of the main screen
    int screenHeight_;

    /// @brief The pointer that points to the ray animation class
    std::unique_ptr<RaylibAnimation> raylibAnimationPtr_;
};

#endif // INCLUDE_GUI_SCREENLIB_H_
