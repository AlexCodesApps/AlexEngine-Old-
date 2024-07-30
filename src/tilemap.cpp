#include "includes/macros/macro_utils.hpp"
#define DEBUG
#include <cmath>
#include <span>
#include <vector>
#include "includes/physics.hpp"
#include "includes/vec2.hpp"
#include "includes/tilemap.hpp"
#include "includes/intalias.hpp"
#include "SDL2/SDL_rect.h"
#include "includes/assets.hpp"
#include "includes/sprites.hpp"
#include "includes/spritesheet.hpp"
#include "includes/macros/debug.hpp"
#include "includes/macros/optional.hpp"
#include <array>
#define DEF_MAP(n, ...) auto n = std::to_array<u8>({__VA_ARGS__});
#define TILE_LIST_X(x) \
x(grass, 1, 0, 1) \
x(lgrass, 0, 0, 2) \
x(rgrass, 2, 0, 3) \
x(dirt, 1, 1, 4) \
x(ldirt, 0, 1, 5) \
x(rdirt, 2, 1, 6) \
x(luckyblock, 3, 0, 7, ENUM_TO_INT(Physics::Data::Bit::Ghost))
#define arr_points_h(_, x, y, ...) {x,y},
namespace {
auto TileCoordinateMap = std::to_array<SDL_Point>({{0, 0}, TILE_LIST_X(arr_points_h)});
#undef arr_points_h
#define flag_h(a,b,c,d, ...) optional_macro(0, __VA_ARGS__) | ENUM_TO_INT(Physics::Data::Bit::Immobile),
auto TileFlagMap = std::to_array<ENUM_INT_TYPE(Physics::Data::Bit)>({TILE_LIST_X(flag_h)});
#undef flag_h
SpriteSheet TileSpriteSheet(Asset::ImageID::Tiles_spritesheet);
std::vector<Physics::Auto> CurrentTiles;
DEF_MAP(world1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
4, 4, 4, 1, 3, 0, 0, 0, 7, 0, 2, 1,
4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4)
DEF_MAP(world2,
0, 0, 2, 1)
auto Tilemaps = std::to_array<std::span<u8>>({world1, world2});
auto TilemapDims = std::to_array<std::pair<u16, u16>>({{12, 8}, {4, 1}});
u8 MapIndex = 0;
} // ANONYMOUS NAMESPACE
void Tilemap::Load() {
    for (u64 y = 0; y < TilemapDims[MapIndex].second; y++) {
        for (u64 x = 0; x < TilemapDims[MapIndex].first; x++) {
            u8 TileID = Tilemaps[MapIndex][y * TilemapDims[MapIndex].first + x];
            if (TileID == 0) continue;
            else CurrentTiles.emplace_back();
            auto new_sprite_id = Sprite::New({x * 16.0f, y * 16.0f, 16.0f, 16.0f},
                TileSpriteSheet.Get(TileCoordinateMap[TileID])
            );
            auto& Tile = CurrentTiles.back().Get();
            Tile.data.Hitbox = {
                0, 0, 16, 16
            };
            Tile.data.Flags = TileFlagMap[TileID-1];
            Tile.spr.GetMut() = Sprite::Get(new_sprite_id);
            Sprite::Remove(new_sprite_id);
        }
    }
}
void Tilemap::Next() {
    MapIndex++;
    if (MapIndex >= Tilemaps.size()) DEBUG_ERROR("TILEMAP LIMIT REACHED");
    CurrentTiles.clear();
    Tilemap::Load();
}

i32 Tilemap::MapWorldF(f32 WPos) {
    return static_cast<i32>(std::floor(WPos / 16.0f));
}

SDL_Point Tilemap::MapWorldF(Vec2 WPos) {
    return {MapWorldF(WPos.x), MapWorldF(WPos.y)};
}

bool Tilemap::PositionIsSolid(Vec2 TPos) {
    const SDL_Point Position = MapWorldF(TPos);
    if (Position.x < 0.0f || Position.x >= TilemapDims[MapIndex].first
        || Position.y < 0.0f || Position.y >= TilemapDims[MapIndex].second) return true;
    const u16 IndexedPosition = Position.y * TilemapDims[MapIndex].first + Position.x;
    return Tilemaps[MapIndex][IndexedPosition] != 0;
}
#undef DEF_MAP

u8 Tilemap::GetTileID(SDL_Point point) {
    return Tilemaps[MapIndex][point.y * TilemapDims[MapIndex].first + point.x];
}

bool Tilemap::TilePositionIsSolid(SDL_Point point) {
    return GetTileID(point) != 0;
}
