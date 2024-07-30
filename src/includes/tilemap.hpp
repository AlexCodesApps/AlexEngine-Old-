#pragma once
#include "SDL2/SDL_rect.h"
#include "intalias.hpp"
#include "vec2.hpp"

namespace Tilemap {
    void Load();
    void Next();
    bool PositionIsSolid(Vec2);
    bool TilePositionIsSolid(SDL_Point);
    u8  GetTileID(SDL_Point);
    i32 MapWorldF(f32);
    SDL_Point MapWorldF(Vec2);
}
