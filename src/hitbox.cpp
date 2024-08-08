#include "includes/hitbox.hpp"

bool Hitbox::PointInRect(const SDL_FRect& rect, Vec2 point) {
    return point.x >= rect.x && (rect.x + rect.w) > point.x &&
           point.y >= rect.y && (rect.y + rect.h) > point.y;
}
