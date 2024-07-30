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
    static void Remove(ID);
    static ID New(SDL_FRect = {0, 0, 16, 16}, Image = Asset::ImageID::undefined, u8 = 0);
    static void DestroyAll();
    static constexpr u64 null_id = 0;
    class Auto {
        ID Tag = null_id;
        public:
        Auto();
        ~Auto();
        Auto(Auto&&);
        Auto& operator=(Auto&&);
        Auto(const Auto&) = delete;
        Auto& operator=(const Auto&) = delete;
        Auto Clone();
        Sprite& GetMut();
        const Sprite& Get();
        ID ID();
    };
    // class Ref {
    //     ID Tag = null_id;
    // public:
    //     Ref() = default;
    //     Ref(ID);
    //     Sprite& Get();
    //     bool Valid();
    //     operator bool();
    // };
};

#endif /* SPRITES_HPP */
