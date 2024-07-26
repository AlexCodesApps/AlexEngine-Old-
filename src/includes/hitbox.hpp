#include "SDL2/SDL_rect.h"
#include "vec2.hpp"

namespace Hitbox {
    using Dimensions = SDL_Rect;
    inline bool IsColliding(const SDL_FRect& A, const SDL_FRect& B) {
        return SDL_HasIntersectionF(&A, &B);
    }
    bool PointInRect(const SDL_FRect&, Vec2);
    bool TilePositionColliding16(Vec2);
    bool TilePositionColliding(const Vec2&, const Dimensions&);
}
