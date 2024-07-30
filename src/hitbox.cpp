#include "includes/hitbox.hpp"
#include "includes/tilemap.hpp"

bool Hitbox::PointInRect(const SDL_FRect & rect, Vec2 point) {
    return point.x >= rect.x && (rect.x + rect.w) > point.x &&
           point.y >= rect.y && (rect.y + rect.h) > point.y;
}

bool Hitbox::TilePositionColliding16(Vec2 Position) {
    return Tilemap::PositionIsSolid(Position) ||
        Tilemap::PositionIsSolid(Vec2{Position.x+16.0f, Position.y}) ||
        Tilemap::PositionIsSolid(Vec2{Position.x, Position.y + 16.0f}) ||
        Tilemap::PositionIsSolid(Vec2{Position.x + 16.0f, Position.y + 16.0f});
}

bool Hitbox::TilePositionColliding(const Vec2& Position, const Dimensions& HitboxDims) {
    const Vec2 BasePosition = {
        Position.x + static_cast<f32>(HitboxDims.x),
        Position.y + static_cast<f32>(HitboxDims.y)
    };
    const Vec2 Offset  = {
        BasePosition.x + static_cast<f32>(HitboxDims.w),
        BasePosition.y + static_cast<f32>(HitboxDims.h)
    };
    return Tilemap::PositionIsSolid(BasePosition)
    || Tilemap::PositionIsSolid({Offset.x, BasePosition.y})
    || Tilemap::PositionIsSolid({BasePosition.x, Offset.y})
    || Tilemap::PositionIsSolid(Offset);
}
