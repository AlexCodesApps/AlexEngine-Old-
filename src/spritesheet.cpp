#include "includes/spritesheet.hpp"

SpriteSheet::SpriteSheet(SDL_Texture * Tex, int _TileSize, int _Margin)
: IMG(Tex), TileSize(_TileSize), Margin(_Margin) {
    TileWidth = IMG.Dimensions.w / TileSize;
    TileHeight = IMG.Dimensions.h / TileSize;
}

Image SpriteSheet::Get(SpriteSheet::Coordinates Coords) {
    return Image(IMG.Texture, SDL_Rect{
        .x = (Coords.x + Margin) * TileSize,
        .y = (Coords.y + Margin) * TileSize,
        .w = TileSize,
        .h = TileSize
    });
}

#define TILES_X(M) \
M(Grass, {1, 0}, testspritesheet) \
M(LeftGrass, {0, 0}, testspritesheet)
