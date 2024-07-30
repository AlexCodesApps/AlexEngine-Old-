#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "macros/macro_utils.hpp"
#include "sprites.hpp"
#include "hitbox.hpp"
namespace Physics {
    struct Data {
        enum class Bit : u8 {
            CollisionUp = BITOFFSET(0),
            CollisionDown = BITOFFSET(1),
            CollisionLeft = BITOFFSET(2),
            CollisionRight = BITOFFSET(3),
            Immobile = BITOFFSET(4),
            Ghost = BITOFFSET(5)

        };
        using Bitset = u8;
        Hitbox::Dimensions Hitbox;
        Vec2 Velocity;
        Vec2 Acceleration;
        Bitset Flags;
        SDL_FRect HitboxToRect(const Vec2& Position) {
            return {
                .x = Position.x + Hitbox.x,
                .y = Position.y + Hitbox.y,
                .w = static_cast<float>(Hitbox.w),
                .h = static_cast<float>(Hitbox.h)
            };
        }
    };
    struct Inst {
        using ID = u64;
        static ID New();
        static Inst& Get(ID);
        static void Remove(ID);
        static void Update();
        Inst Clone();
        Data data;
        Sprite::Auto spr;
    };
    class Auto {
        Inst::ID Tag;
        Auto(Inst::ID);
        public:
        Auto();
        Auto(const Auto&) = delete;
        Auto& operator=(const Auto&) = delete;
        Auto(Auto&&);
        Auto& operator=(Auto&&);
        ~Auto();
        Inst& Get();
        Auto Clone();
    };
}

#endif /* PHYSICS_HPP */
