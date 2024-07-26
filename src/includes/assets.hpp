#pragma once
#include "SDL2/SDL_render.h"

#define PLAYER_SPRITESHEET Carl_spritesheet
#define TILES_SPRITESHEET Tiles_spritesheet
#define MISC_IMAGES undefined, circle, white, Carl
#define TILEMAPS world1
#define IMAGES_ALL PLAYER_SPRITESHEET, TILES_SPRITESHEET, MISC_IMAGES
#define UNKNOWN_IMAGE ::Asset::ImageID::undefined

namespace Asset {
    enum class ImageID {
        IMAGES_ALL
    };
    bool LoadAll(SDL_Renderer *);
    SDL_Texture *GetTexture(ImageID);
    void DestroyAll();
}
