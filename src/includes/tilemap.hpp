#pragma once
#include "IRenderable.hpp"
#include "macroutils.hpp"
#include "textures.hpp"
#define TILE_COORD_PAIRS_X(M) \
M(Luckyblock, 1, 1) \
M(Grass, 2, 6) \
M(CloudGuy, 5, 0)
typedef SDL_Point TileCoordinates;
#define TextureCoordPairs(n, x, y) inline auto mario_tile_##n = TileCoordinates{x, y};

TILE_COORD_PAIRS_X(TextureCoordPairs)

struct SpriteSheet {
    Image IMG;
    SpriteSheet(SDL_Texture* Tex)
    : IMG(Tex) {}

};

struct Tile {
    enumerate(Kind, TILES);
    static constexpr int Width = 16;
};
