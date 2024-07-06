#include "includes/renderable.hpp"

Image::Image(Asset::ImageID ID)
: ID(ID) {
    SDL_QueryTexture(Asset::GetTexture(ID), NULL, NULL, &Dimensions.w, &Dimensions.h);
}

Image::Image(Asset::ImageID ID, const SDL_Rect& Dims)
: ID(ID), Dimensions(Dims) {}

RenderableEntity::RenderableEntity(Image _IMG, SDL_FRect _Body)
: IMG(_IMG), Body(_Body) {}

SDL_FRect RenderableEntity::TranslateLocation(Vec2 NewLoc) {
    return SDL_FRect {
        .x = NewLoc.x,
        .y = NewLoc.y,
        .w = Body.w,
        .h = Body.h
    };
}

void RenderableEntity::SetLocation(Vec2 NewLoc) {
    Body.x = NewLoc.x;
    Body.y = NewLoc.y;
}

void RenderableEntity::ChangeLocation(Vec2 ChangeLoc) {
    Body.x += ChangeLoc.x;
    Body.y += ChangeLoc.y;
}

Vec2 operator+(Vec2 a, Vec2 b) {
    return {a.x + b.x, a.y + b.y};
}

Vec2 operator-(Vec2 a, Vec2 b) {
    return {a.x - b.x, a.y - b.y};
}

Vec2 operator+(Vec2 a, const SDL_FRect& b) {
    return {a.x + b.x, a.y + b.y};
}

SDL_FRect& SDL_FRectSetXY(SDL_FRect& s, Vec2 p) {
    s.x = p.x; s.y = p.y;
    return s;
}
