#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "SDL2/SDL_rect.h"
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
            Ghost = BITOFFSET(5),
            Dangerous = BITOFFSET(6),
            CollidingDangerous = BITOFFSET(7)
        };
        using Bitset = u8;
        Hitbox::Dimensions Hitbox{};
        Vec2 Velocity{};
        Vec2 Acceleration{};
        Bitset Flags{};
        SDL_FRect HitboxToRect(Vec2 Position) {
            return {
                .x = Position.x + Hitbox.x,
                .y = Position.y + Hitbox.y,
                .w = static_cast<float>(Hitbox.w),
                .h = static_cast<float>(Hitbox.h)
            };
        }
    };
    struct Entity {
        using ID = u64;
        static ID New(Sprite::Ref, const Data&);
        static ID New(const Entity&);
        static ID New();
        static Entity& Get(ID);
        static void Remove(ID);
        static void Update();
        Data PhysData{};
        Sprite::Ref SpriteRef{};
    };
    class Auto {
        Entity::ID Tag;
        public:
        Auto(Entity::ID);
        Auto();
        Auto(Sprite::Ref, const Data&);
        Auto(const Auto&) = delete;
        Auto& operator=(const Auto&) = delete;
        Auto(Auto&&);
        Auto& operator=(Auto&&);
        ~Auto();
        Entity& Get();
        Auto Clone(Sprite::Ref);
    };
}

#endif /* PHYSICS_HPP */
