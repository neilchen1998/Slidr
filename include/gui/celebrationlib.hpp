#ifndef INCLUDE_GUI_CELEBRATIONLIB_H_
#define INCLUDE_GUI_CELEBRATIONLIB_H_

#include <vector>   // std::vector

#include "raylib.h"
#include "math/mathlib.hpp"
#include "gui/colourlib.hpp"

struct Confetti
{
    Vector2 position;
    Vector2 velocity;
    Vector2 size;
    float rotation;
    float omega;
    Color color;
    bool active;
};

namespace
{
    constexpr float GRAVITY = 200.0;
    constexpr size_t MAX_NUM_CONFETTI = 500;

    std::array<Color, 6> CONFETTI_COLOURS { LIGHT_CORAL, APRICOT, LEMON, MINT, SKY_BLUE, LAVENDER };
}

class Celebration
{
public:
    Celebration();

    /// @brief Updates the confetti
    void Update();

    /// @brief Draws the confetti
    void Draw() const;

private:
    /// @brief Spawns a single confetti
    void SpawnConfetti();

private:
    /// @brief 
    std::vector<Confetti> confetti_;
};

#endif // INCLUDE_GUI_CELEBRATIONLIB_H_