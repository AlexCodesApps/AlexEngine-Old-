#pragma once
#include "IRenderable.hpp"

namespace Player {
    enum class Direction {
        Left,
        Right
    };
    namespace Camera {
        extern SDL_FPoint GetRelativePosition(SDL_FPoint);
    }
    extern void Load();
    extern const SDL_FPoint& GetPosition();
    extern void ChangePosition(const SDL_FPoint&);
    extern void ChangeDirection(Direction);
    extern void Draw();
    extern void Update();
}
