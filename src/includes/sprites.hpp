#ifndef SPRITES_HPP
#define SPRITES_HPP
#include "assets.hpp"
#include "renderable.hpp"
#include <cstddef>

class Sprite {
public:
    using ID = size_t;
    static void DrawAll();
    RenderableEntity Entity;
    SDL_FRect Body = {0, 0, 16, 16};
    float Scale = 1;
    float ZOffset = 0;
    Uint8 Layer = 0;
    static Sprite& Get(ID);
    static void Remove(ID);
    static ID New(SDL_FRect = {0, 0, 16, 16}, Image = Asset::ImageID::undefined, Uint8 = 0);
    static bool Colliding(ID);
    static void DestroyAll();
    class Auto {
        static constexpr size_t NULL_ID = 0;
        ID Tag = NULL_ID;
        public:
        Auto();
        ~Auto();
        Auto(Auto&&);
        Auto& operator=(Auto&&);
        Auto(const Auto&) = delete;
        Auto& operator=(const Auto&) = delete;
        Auto Clone();
        Sprite& Get();
        ID GetID();
    };
};

#endif /* SPRITES_HPP */
