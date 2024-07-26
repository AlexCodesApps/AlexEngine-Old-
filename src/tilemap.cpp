#define DEBUG
#include <cmath>
#include <ranges>
#include <span>
#include <vector>
#include "includes/vec2.hpp"
#include "includes/tilemap.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_stdinc.h"
#include "includes/assets.hpp"
#include "includes/sprites.hpp"
#include "includes/spritesheet.hpp"
#include "includes/macros/debug.hpp"
#include <array>
#define DEF_MAP(n, ...) auto n = std::to_array<Uint8>({__VA_ARGS__});
#define TILE_LIST_X(x) \
x(grass, 1, 0, 1) \
x(lgrass, 0, 0, 2) \
x(rgrass, 2, 0, 3) \
x(dirt, 1, 1, 4) \
x(ldirt, 0, 1, 5) \
x(rdirt, 2, 1, 6)
#define arr_points_h(_, x, y, ...) {x,y},
namespace {
auto TileCoordinateMap = std::to_array<SDL_Point>({{0, 0}, TILE_LIST_X(arr_points_h)});
#undef arr_points_h
SpriteSheet TileSpriteSheet(Asset::ImageID::Tiles_spritesheet);
std::vector<Sprite::ID> CurrentTiles;
DEF_MAP(world1,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
1, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
4, 4, 4, 1, 3, 0, 0, 0, 0, 0, 2, 1,
4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 4, 4,
4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4)
DEF_MAP(world2,
0, 0, 2, 1)
auto Tilemaps = std::to_array<std::span<Uint8>>({world1, world2});
auto TilemapDims = std::to_array<std::pair<Uint16, Uint16>>({{12, 8}, {4, 1}});
Uint8 MapIndex = 0;
} // ANONYMOUS NAMESPACE
void Tilemap::Load() {
    for (size_t y = 0; y < TilemapDims[MapIndex].second; y++) {
        for (size_t x = 0; x < TilemapDims[MapIndex].first; x++) {
            Uint8 TileID = Tilemaps[MapIndex][y * TilemapDims[MapIndex].first + x];
            if (TileID == 0) continue;
            else CurrentTiles.emplace_back(Sprite::New({x * 16.0f, y * 16.0f, 16.0f, 16.0f},
                TileSpriteSheet.Get(TileCoordinateMap[TileID])
            ));
        }
    }
}
void Tilemap::Next() {
    MapIndex++;
    if (MapIndex >= Tilemaps.size()) DEBUG_ERROR("TILEMAP LIMIT REACHED");
    for (auto id : std::views::reverse(CurrentTiles)) {
        Sprite::Remove(id);
    }
    CurrentTiles.clear();
    Tilemap::Load();
}

int Tilemap::MapWorldF(float WPos) {
    return static_cast<int>(std::floor(WPos / 16.0f));
}

SDL_Point Tilemap::MapWorldF(Vec2 WPos) {
    return {MapWorldF(WPos.x), MapWorldF(WPos.y)};
}

bool Tilemap::PositionIsSolid(Vec2 TPos) {
    const SDL_Point Position = MapWorldF(TPos);
    if (Position.x < 0.0f || Position.x >= TilemapDims[MapIndex].first
        || Position.y < 0.0f || Position.y >= TilemapDims[MapIndex].second) return true;
    const Uint16 IndexedPosition = Position.y * TilemapDims[MapIndex].first + Position.x;
    return Tilemaps[MapIndex][IndexedPosition] != 0.0f;
}
#undef DEF_MAP

bool Tilemap::TilePositionIsSolid(SDL_Point point) {
    return Tilemaps[MapIndex][point.y * TilemapDims[MapIndex].first + point.x] != 0;
}

Vec2 Tilemap::CorrectPosition(Vec2 WPos, bool XSolid, bool YSolid) {
    if (XSolid) WPos.x = std::floor(WPos.x);
    if (YSolid) WPos.x = std::floor(WPos.y);
    return WPos;
}
