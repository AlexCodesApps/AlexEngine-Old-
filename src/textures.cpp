#define DEBUG
#include "includes/textures.hpp"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "includes/macroutils.hpp"
#include <SDL2/SDL_image.h>
#include <cstdint>
#include <iostream>
#include <vector>

namespace Texture {
    #define for_each_tex(macro) for_each_macro(macro, TEXTURE_LIST)
    #define decl_texture_v(e) SDL_Texture * tex_##e = nullptr;
    for_each_tex(decl_texture_v)
    bool LoadAll(SDL_Renderer * Renderer) {
        #define load_asset_h(e) {\
            tex_##e = IMG_LoadTexture(Renderer, "assets/" #e ".png");\
            if (tex_##e == nullptr) {\
                DestroyAll();\
                std::cerr << "Texture failed to load - assets/" #e ".png - Code : " << IMG_GetError();\
                return false;\
            }\
        }
        for_each_tex(load_asset_h);
        DEBUG_LOG("All Textures Loaded");
        return true;
    }
    SDL_Texture * Get(Asset Tenum) {
        #define texture_case(e) case (Asset::e) : return tex_##e;
        switch (Tenum) {
            for_each_tex(texture_case)
        }
    }
    std::vector<SDL_Texture*> Dynamic_Textures;
    void DestroyAll() {
        #define destroy_sprite(e) \
        if (tex_##e != nullptr) SDL_DestroyTexture(tex_##e);
        for_each_tex(destroy_sprite)
        for (auto& tex : Dynamic_Textures) {
            SDL_DestroyTexture(tex);
        }
    }
    SDL_Texture *CreateMonoTexture(SDL_Renderer* Renderer, SDL_Color color) {
        auto tex = SDL_CreateTexture(Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, 1, 1);
        SDL_UpdateTexture(tex, nullptr, &color, sizeof(uint32_t));
        Dynamic_Textures.push_back(tex);
        return tex;
    }
}
#undef for_each_tex
#undef decl_texture_v
#undef load_asset_h
#undef texture_case
#undef destroy_sprite
