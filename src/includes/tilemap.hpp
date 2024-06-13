#pragma once
#include "IRenderable.hpp"
#include "macroutils.hpp"
#include "textures.hpp"
#define TEXTURE_TILES Grass
#define COLOR_TILES Skyblue
#define SPECIAL_TILES PlayerSpawn
#define TILES TEXTURE_TILES, COLOR_TILES, SPECIAL_TILES
typedef SDL_Point TileCoordinates;
struct SpriteSheet {
    Image IMG;
    SpriteSheet(SDL_Texture* Tex)
    : IMG(Tex) {}

};

struct Tile {
    enumerate(Kind, TILES);
    static constexpr int Width = 16;
};
