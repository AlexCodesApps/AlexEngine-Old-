#ifndef SPRITES_HPP
#define SPRITES_HPP
#include "assets.hpp"
#include "renderable.hpp"
#include <cstddef>

class Sprite {
public:
    using ID = size_t;
private:
    static ID IDCounter;
public:
    static void DrawAll();
    RenderableEntity Entity;
    SDL_FRect Body = {0, 0, 16, 16};
    float Scale = 1;
    float ZOffset = 0;
    static Sprite& Get(ID);
    static void Remove(ID);
    static ID New(SDL_FRect = {0, 0, 16, 16}, Image = Asset::ImageID::undefined);
};

#endif /* SPRITES_HPP */
