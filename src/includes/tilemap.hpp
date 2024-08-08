#pragma once
#include "SDL2/SDL_rect.h"
#include "intalias.hpp"
#include "vec2.hpp"

namespace Tilemap {
    void Load();
    void Next();
    bool IsLastLevel();
    u8  GetTileID(SDL_Point);
    u8 GetPositionTileID(Vec2);
    i32 MapWorldF(f32);
    SDL_Point MapWorldF(Vec2);
}
