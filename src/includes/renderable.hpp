#pragma once
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_image.h>
#include "assets.hpp"
#include "vec2.hpp"

struct Image {
    Asset::ImageID ID = Asset::ImageID::undefined;
    SDL_Rect Dimensions = {};
    Image() = default;
    Image(Asset::ImageID);
    Image(Asset::ImageID, SDL_Rect);
};

struct RenderableEntity {
    Image IMG;
    SDL_FRect Body;
    RenderableEntity() = default;
    RenderableEntity(const Image&, const SDL_FRect&);
    SDL_FRect TranslateLocation(Vec2);
    void SetLocation(Vec2);
    void ChangeLocation(Vec2);
};
Vec2 operator+(Vec2 a, Vec2 b);
Vec2 operator-(Vec2 a, Vec2 b);
Vec2 operator+(Vec2 a, const SDL_FRect& b);
SDL_FRect& SDL_FRectSetXY(SDL_FRect&, Vec2);
