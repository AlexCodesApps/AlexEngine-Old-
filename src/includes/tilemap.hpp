#pragma once
#include "spritesheet.hpp"
#include <vector>

namespace Tiles {
    class IMap {
        size_t size;
        std::vector<Uint8> Map;
        SpriteSheet& S;
        IMap(const SpriteSheet&);
    };
}
