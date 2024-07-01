#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_image.h>
#include <cstddef>
#include "vec2.hpp"

struct Image {
    SDL_Texture * Texture;
    SDL_Rect Dimensions = {0};
    Image() = default;
    Image(SDL_Texture * _Texture)
    : Texture(_Texture) {
        SDL_QueryTexture(_Texture, NULL, NULL, &Dimensions.w, &Dimensions.h);
    }
    Image(SDL_Texture * IMG, const SDL_Rect& Dims)
    : Texture(IMG), Dimensions(Dims) {}
};

struct RenderableEntity {
    Image IMG;
    SDL_FRect Body;
    RenderableEntity() = default;
    RenderableEntity(Image _IMG, SDL_FRect _Body)
    : IMG(_IMG), Body(_Body) {}
    SDL_FRect TranslateLocation(Vec2 NewLoc) {
        return SDL_FRect {
            .x = NewLoc.x,
            .y = NewLoc.y,
            .w = Body.w,
            .h = Body.h
        };
    }
    void SetLocation(Vec2 NewLoc) {
        Body.x = NewLoc.x;
        Body.y = NewLoc.y;
    }
    void ChangeLocation(Vec2 ChangeLoc) {
        Body.x += ChangeLoc.x;
        Body.y += ChangeLoc.y;
    }
};

inline Vec2 operator+(Vec2 a, Vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

inline Vec2 operator-(Vec2 a, Vec2 b) {
    return {a.x - b.x, a.y - b.y};
}

inline Vec2 operator+(Vec2 a, const SDL_FRect& b) {
    return {a.x + b.x, a.y + b.y};
}

inline SDL_FRect& SDL_FRectSetXY(SDL_FRect& s, Vec2 p) {
    s.x = p.x; s.y = p.y;
    return s;
}
