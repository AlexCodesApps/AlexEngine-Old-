#pragma once
#include "IRenderable.hpp"
#include <cstddef>

struct SpriteSheet {
    typedef SDL_Point Coordinates;
    int TileSize = 16;
    int TileWidth;
    int TileHeight;
    int Margin = 0;
    Image IMG;
    SpriteSheet() = default;
    SpriteSheet(SDL_Texture*, int = 16, int = 0);
    Image Get(Coordinates);
};
