#pragma once
#include "assets.hpp"
#include "renderable.hpp"
#include <cstddef>

struct SpriteSheet {
    typedef SDL_Point Coordinates;
    Image IMG;
    int TileSize = 16;
    int TileWidth;
    int TileHeight;
    int Margin = 0;
    SpriteSheet() = default;
    SpriteSheet(Asset::ImageID, int = 16, int = 0);
    Image Get(Coordinates);
};
