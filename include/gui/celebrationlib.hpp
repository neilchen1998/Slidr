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

    std::array<Color, 6> CONFETTI_COLOURS {LIGHT_CORAL, APRICOT, LEMON, MINT, SKY_BLUE, LAVENDER};
}

class Celebration
{
public:
    Celebration()
    {
        confetti_.resize(MAX_NUM_CONFETTI);

        auto itr = confetti_.begin();
        while (itr != confetti_.end())
        {
            itr->active = false;

            ++itr;
        }
    }

    void Update()
    {
        // Generate 5 confetti at a time
        for (size_t i = 0; i < 5; i++)
        {
            SpawnConfetti();
        }
        
        // Get the delta time
        float deltaT = GetFrameTime();

        auto itr = confetti_.begin();
        while (itr != confetti_.end())
        {
            // Only update the confetti that is active
            if (itr->active)
            {
                // Apply gravity
                itr->velocity.y += GRAVITY * deltaT;

                // Calculate the new position & angular position
                itr->position.x += itr->velocity.x * deltaT;
                itr->position.y += itr->velocity.y * deltaT;
                itr->rotation += itr->omega * deltaT;

                // Check if the confetti is still on the screen
                if (itr->position.y > GetScreenHeight() + 10)
                {
                    itr->active = false;
                }
            }

            ++itr;
        }
    }

    void Draw() const
    {
        auto itr = confetti_.cbegin();
        while (itr != confetti_.cend())
        {
            if (itr->active)
            {
                Rectangle rec = { itr->position.x, itr->position.y, itr->size.x, itr->size.y };
                Vector2 origin = { (itr->position.x / 2), (itr->position.y / 2) };

                DrawRectanglePro(rec, origin, itr->rotation, itr->color);
            }
            ++itr;
        }
    }

private:
    void SpawnConfetti()
    {
        auto itr = confetti_.begin();
        while (itr != confetti_.end())
        {
            if (!itr->active)
            {
                itr->active = true;
                itr->position = (Vector2){ (float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(-GetScreenHeight() * 0.25, 0) };
                itr->velocity = (Vector2){ (float)GetNormalFloatDist(-100, 100), (float)GetNormalFloatDist(-100, 100) };
                itr->size = (Vector2){ (float)GetRandomValue(5, 12), (float)GetRandomValue(8, 20) };
                itr->rotation = (float)GetRandomValue(0, 360);
                itr->omega = (float)GetNormalFloatDist(-150, 150);
                itr->color = CONFETTI_COLOURS[GetUniformIntDist(0, CONFETTI_COLOURS.size() - 1)];
                break;
            }

            ++itr;
        }
    }

private:
    std::vector<Confetti> confetti_;
};

#endif // INCLUDE_GUI_CELEBRATIONLIB_H_