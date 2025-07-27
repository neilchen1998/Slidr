#ifndef INCLUDE_GUI_ANIMATIONLIB_H_
#define INCLUDE_GUI_ANIMATIONLIB_H_

#include "raylib.h"

/// @brief The states of the game
enum struct LoadingState : int
{
    SMALL_BOX_BLINKING = 0,
    LEFT_BOX_GROWING,
    RIGHT_BOX_GROWING,
    LETTER_APPEARING,
    ENDING
};

class LoadingAnimation
{
public:
    LoadingAnimation(int screenWidth, int screenHeight)
        : curState_(LoadingState::SMALL_BOX_BLINKING),
        screenWidth_(screenWidth),
        screenHeight_(screenHeight),
        logoPositionX_(screenWidth/2 - 128),
        logoPositionY_(screenHeight/2 - 128),
        leftSideRecHeight_(16),
        topSideRecWidth_(16),
        bottomSideRecWidth_(16),
        rightSideRecHeight_(16),
        lettersCount_(0),
        framesCounter_(0),
        alpha_(1.0f),
        totalCnt_(0)
    {
    }

    ~LoadingAnimation() = default;

    /// @brief Update the state
    void Update();

    /// @brief Draw the the state on the screen
    void Draw();

private:
    /// @brief The current state of the game
    LoadingState curState_;

    /// @brief The width of the main screen
    int screenWidth_;

    /// @brief The height of the main screen
    int screenHeight_;

    int leftSideRecHeight_;

    int topSideRecWidth_;

    int lettersCount_;

    float alpha_;

    const int logoPositionX_;

    const int logoPositionY_;

    /// @brief 
    int bottomSideRecWidth_;

    int rightSideRecHeight_;

    unsigned long framesCounter_;

    unsigned totalCnt_;
};

#endif // INCLUDE_GUI_ANIMATIONLIB_H_
