#ifndef HITBOX_HPP
#define HITBOX_HPP

#include "SDL2/SDL_rect.h"
#include "vec2.hpp"

namespace Hitbox {
    using Dimensions = SDL_Rect;
    inline bool IsColliding(const SDL_FRect& A, const SDL_FRect& B) {
        return SDL_HasIntersectionF(&A, &B);
    }
    bool PointInRect(const SDL_FRect&, Vec2);
}

#endif /* HITBOX_HPP */
