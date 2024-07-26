#include "includes/spritesheet.hpp"

SpriteSheet::SpriteSheet(Asset::ImageID ID, i32 _TileSize, i32 _Margin)
: IMG(ID), TileSize(_TileSize), Margin(_Margin) {
    TileWidth = IMG.Dimensions.w / TileSize;
    TileHeight = IMG.Dimensions.h / TileSize;
}

Image SpriteSheet::Get(SpriteSheet::Coordinates Coords) {
    return Image(IMG.ID, SDL_Rect{
        .x = (Coords.x + Margin) * TileSize,
        .y = (Coords.y + Margin) * TileSize,
        .w = TileSize,
        .h = TileSize
    });
}
