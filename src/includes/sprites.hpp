#ifndef SPRITES_HPP
#define SPRITES_HPP
#include "intalias.hpp"
#include "assets.hpp"
#include "renderable.hpp"
#include <cstddef>

class Sprite {
public:
    using ID = u64;
    static void DrawAll();
    RenderableEntity Entity;
    SDL_FRect Body = {0, 0, 16, 16};
    f32 Scale = 1;
    f32 ZOffset = 0;
    u8 Layer = 0;
    static Sprite& GetMut(ID);
    static const Sprite& Get(ID);
    static bool Valid(ID);
    static void Remove(ID);
    static ID New(const SDL_FRect& = {0, 0, 16, 16}, const Image& = Asset::ImageID::undefined, u8 = 0);
    static ID New(const Sprite&);
    static void DestroyAll();
    class Auto {
        ID Tag = 0;
        public:
        Auto(const SDL_FRect& = {0, 0, 16, 16}, const Image& = Asset::ImageID::undefined, u8 = 0);
        ~Auto();
        Auto(Auto&&);
        Auto& operator=(Auto&&);
        Auto(const Auto&) = delete;
        Auto& operator=(const Auto&) = delete;
        Auto Clone();
        Sprite& GetMut();
        const Sprite& Get();
        ID GetID();
    };
    class Ref {
        ID Tag = 0;
    public:
        Ref() = default;
        Ref(ID);
        const Sprite& Get();
        Sprite& GetMut();
        bool Valid();
        operator bool();
        ID GetID();
    };
};

#endif /* SPRITES_HPP */
