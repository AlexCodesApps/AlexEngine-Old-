#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "sprites.hpp"
#include "hitbox.hpp"
#include <bitset>
namespace Physics {
    struct Data {
        using Bitset = std::bitset<8>;
        Hitbox::Dimensions Hitbox;
        Vec2 Velocity;
        Vec2 Acceleration;
        u8 Flags;
    };
    struct Inst {
        using ID = u64;
        static Inst New();
        static void Remove(ID);
        Data data;
        Sprite::Auto spr;
    };
}

#endif /* PHYSICS_HPP */
