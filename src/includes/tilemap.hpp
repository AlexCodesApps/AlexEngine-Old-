#pragma once
#define DEBUG
#include "../tilemap/metatile.hpp"
#include "macroutils.hpp"
#include "spritesheet.hpp"
#include <bitset>

#define TILEMAP_LIST world1

namespace Tile {
    enumerate_macro(Maps, TILEMAP_LIST);
    struct Data {
        enum class Flags : Uint8 {
            Air = BITOFFSET(0),
            Ghost = BITOFFSET(1),
            Dangerous = BITOFFSET(2)
        };
        SpriteSheet::Coordinates Asset;
        std::bitset<ENUM_SIZE(Flags) * BYTE_SIZE> Flags;
    };
    extern void LoadAssets();
    extern MetaTile::TextureData GetTextureData(std::string);
    extern MetaTile::TilemapData GetTilemapData(std::string);
    extern Data GetTileData(Maps, size_t id);
}
