#pragma once
#include "SDL2/SDL_rect.h"
#include "vec2.hpp"

namespace Tilemap {
    void Load();
    void Next();
    bool PositionIsSolid(Vec2);
    bool TilePositionIsSolid(SDL_Point);
    int MapWorldF(float);
    SDL_Point MapWorldF(Vec2);
    Vec2 CorrectPosition(Vec2, bool XSolid, bool YSolid);
}
