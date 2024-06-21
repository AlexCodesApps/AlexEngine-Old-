#include "macroutils.hpp"
#include "SDL2/SDL_render.h"

#define TEXTURE_LIST \
white, circle, testspritesheet, playerplaceholder
namespace Texture {
    enumerate(Asset, TEXTURE_LIST)
    extern bool LoadAll(SDL_Renderer *);
    extern SDL_Texture *Get(Asset);
    extern void DestroyAll();
    extern SDL_Texture *CreateMonoTexture(SDL_Renderer*,SDL_Color);
}
