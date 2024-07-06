#define DEBUG
#include "includes/assets.hpp"
#include "SDL2/SDL_render.h"
#include "includes/macroutils.hpp"
#include "SDL2/SDL_image.h"
#define IMAGE_PATH "assets/images/"
#define IMAGE_FILE(x) IMAGE_PATH #x ".png"
namespace Asset {
    SDL_Texture * Images[list_size_macro(IMAGES_ALL)];
    #define LOAD_IMAGE(x) { \
        constexpr auto address = ENUM_TO_NUMBER(ImageID::x); \
        Images[address] = IMG_LoadTexture(Renderer, IMAGE_FILE(x)); \
        if (!Images[address]) { \
            DEBUG_EXPAND(DestroyAll()); \
            DEBUG_ERROR("INVALID FILE {}", IMAGE_FILE(x)); \
            return false; \
        } \
    }
    bool LoadAll(SDL_Renderer * Renderer) {
        for_each_macro(LOAD_IMAGE, IMAGES_ALL);
        return true;
    };
    SDL_Texture * GetTexture(ImageID IMG_N) {
        return Images[ENUM_TO_NUMBER(IMG_N)];
    }
    void DestroyAll() {
        for (auto Image : Images) {
            SDL_DestroyTexture(Image);
        }
    }
}
