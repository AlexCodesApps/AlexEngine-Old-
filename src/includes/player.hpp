#pragma once
#include "IRenderable.hpp"

namespace Player {
    namespace Camera {
        extern SDL_FPoint GetRelativePosition(SDL_FPoint);
    }
    extern void Load();
    extern const RenderableEntity& GetSprite();
    extern const SDL_FPoint& GetPosition();
    extern void ChangePosition(const SDL_FPoint&);
    extern void Draw();
}
