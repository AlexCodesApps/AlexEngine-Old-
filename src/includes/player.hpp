#pragma once
#include <SDL2/SDL_rect.h>
#include "vec2.hpp"

namespace Player {
    enum class Direction {
        Left,
        Right
    };
    enum class Action {
        Idling,
        Walking,
    };
    namespace State {
        extern Action CurrentAction;
        extern Direction CurrentDirection;
    };
    namespace Camera {
        extern Vec2 GetRelativePosition(SDL_FRect);
    }
    constexpr float Speed = 30.0f;
    extern void Load();
    extern Vec2 GetPosition();
    extern void SetPosition(Vec2);
    extern void ChangePosition(Vec2);
    extern void UpdateAnimation();
    extern void Draw();
    extern void Update();
}
