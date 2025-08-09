#ifndef INCLUDE_GUI_SCREENLIB_H_
#define INCLUDE_GUI_SCREENLIB_H_

#include <memory>   // std::unique_ptr, std::make_unique

#include "gui/animationlib.hpp"
#include "gui/board.hpp"
#include "gui/celebrationlib.hpp"   // Celebration

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
        raylibAnimationPtr_(std::make_unique<RaylibAnimation>(screenWidth_, screenHeight_)),
        boardPtr_(std::make_unique<Board>(screenWidth_, screenHeight_)),
        celebrationPtr_(std::make_unique<Celebration>())
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

    /// @brief The pointer that points to the Board class
    std::unique_ptr<Board> boardPtr_;

    /// @brief The pointer that points to the Celebration class
    std::unique_ptr<Celebration> celebrationPtr_;
};

#endif // INCLUDE_GUI_SCREENLIB_H_
