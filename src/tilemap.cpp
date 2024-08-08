#include <utility>
#define DEBUG
#include <array>
#include <cmath>
#include <span>
#include <vector>
#include <type_traits>
#include "includes/player.hpp"
#include "includes/physics.hpp"
#include "includes/vec2.hpp"
#include "includes/tilemap.hpp"
#include "includes/intalias.hpp"
#include "SDL2/SDL_rect.h"
#include "includes/assets.hpp"
#include "includes/sprites.hpp"
#include "includes/spritesheet.hpp"
#include "includes/macros/debug.hpp"
// x(TILE_NAME, X, Y, ID, Flags)
#define TILE_LIST_X(x) \
x(grass, 1, 0, 1, 0) \
x(lgrass, 0, 0, 2, 0) \
x(rgrass, 2, 0, 3, 0) \
x(dirt, 1, 1, 4, 0) \
x(ldirt, 0, 1, 5, 0) \
x(rdirt, 2, 1, 6, 0) \
x(luckyblock, 3, 0, 7, std::to_underlying(Physics::Data::Bit::Ghost)) \
x(spike, 3, 1, 8, std::to_underlying(Physics::Data::Bit::Dangerous) | std::to_underlying(Physics::Data::Bit::Ghost))
#define arr_points_h(_, x, y, ...) {x,y},
namespace {
auto TileCoordinateMap = std::to_array<SDL_Point>({{0, 0}, TILE_LIST_X(arr_points_h)});
#undef arr_points_h
#define flag_h(a,b,c,d,e, ...) e | std::to_underlying(Physics::Data::Bit::Immobile),
auto TileFlagMap = std::to_array<std::underlying_type_t<Physics::Data::Bit>>({TILE_LIST_X(flag_h)});
#undef flag_h
SpriteSheet TileSpriteSheet(Asset::ImageID::Tiles_spritesheet);
std::vector<Physics::Auto> CurrentTiles;
#define DEF_MAP(n, ...) auto n = std::to_array<u8>({__VA_ARGS__});
DEF_MAP(world1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 8, 0,
4, 4, 4, 1, 3, 0, 0, 0, 7, 0, 2, 1,
4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4)
DEF_MAP(world2,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 8, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 7,
0, 0, 2, 1, 1, 1, 3, 0, 0, 5, 4, 3, 0, 0, 0, 0, 0, 2, 1, 1,
1, 1, 4, 4, 4, 4, 4, 3, 0, 0, 0, 0, 0, 2, 1, 3, 0, 5, 4, 6,)
auto Tilemaps = std::to_array<std::span<u8>>({world1, world2});
auto TilemapDims = std::to_array<std::pair<u16, u16>>({{12, 8}, {20, 5}});
auto SpawnCoords = std::to_array<SDL_Point>({{4, 3}, {0, 3}});
u8 MapIndex = 0;
} // ANONYMOUS NAMESPACE
void Tilemap::Load() {
    for (u64 y = 0; y < TilemapDims[MapIndex].second; y++) {
        for (u64 x = 0; x < TilemapDims[MapIndex].first; x++) {
            u8 TileID = Tilemaps[MapIndex][y * TilemapDims[MapIndex].first + x];
            if (TileID == 0) continue;
            auto new_sprite_id = Sprite::New({x * 16.0f, y * 16.0f, 16.0f, 16.0f},
                TileSpriteSheet.Get(TileCoordinateMap[TileID])
            );
            CurrentTiles.emplace_back(new_sprite_id, Physics::Data{
                .Hitbox = {
                    0, 0, 16, 16
                },
                .Flags = TileFlagMap[TileID-1]
            });
        }
    }
    Player::SetPosition({
        SpawnCoords[MapIndex].x * 16.0f,
        SpawnCoords[MapIndex].y * 16.0f
    });
}
void Tilemap::Next() {
    if (Tilemap::IsLastLevel()) DEBUG_ERROR("TILEMAP LIMIT REACHED");
    MapIndex++;
    for (auto& EntityHandle : CurrentTiles) {
        Sprite::Remove(EntityHandle.Get().SpriteRef.GetID());
    }
    CurrentTiles.clear();
    Tilemap::Load();
}

bool Tilemap::IsLastLevel() {
    return (MapIndex+1) >= Tilemaps.size();
}

i32 Tilemap::MapWorldF(f32 WPos) {
    return static_cast<i32>(std::floor(WPos / 16.0f));
}

SDL_Point Tilemap::MapWorldF(Vec2 WPos) {
    return {MapWorldF(WPos.x), MapWorldF(WPos.y)};
}

#undef DEF_MAP

u8 Tilemap::GetTileID(SDL_Point point) {
    return Tilemaps[MapIndex][point.y * TilemapDims[MapIndex].first + point.x];
}

u8 Tilemap::GetPositionTileID(Vec2 point) {
    return Tilemap::GetTileID(Tilemap::MapWorldF(point));
}
