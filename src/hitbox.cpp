#include "includes/hitbox.hpp"
#include "includes/tilemap.hpp"

bool Hitbox::PointInRect(const SDL_FRect & rect, Vec2 point) {
    return point.x >= rect.x && (rect.x + rect.w) > point.x &&
           point.y >= rect.y && (rect.y + rect.h) > point.y;
}

bool Hitbox::TilePositionColliding16(Vec2 Position) {
    if  (Tilemap::PositionIsSolid(Position) ||
        Tilemap::PositionIsSolid(Vec2{Position.x+16.0f, Position.y}) ||
        Tilemap::PositionIsSolid(Vec2{Position.x, Position.y + 16.0f}) ||
        Tilemap::PositionIsSolid(Vec2{Position.x + 16.0f, Position.y + 16.0f})
    ) return true;
    return false;
}
