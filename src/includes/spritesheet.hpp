#pragma once
#include "assets.hpp"
#include "intalias.hpp"
#include "renderable.hpp"
#include <cstddef>

struct SpriteSheet {
    typedef SDL_Point Coordinates;
    Image IMG;
    i32 TileSize = 16;
    i32 TileWidth;
    i32 TileHeight;
    i32 Margin = 0;
    SpriteSheet() = default;
    SpriteSheet(Asset::ImageID, i32 = 16, i32 = 0);
    Image Get(Coordinates);
};
