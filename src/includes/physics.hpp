#ifndef PHYSICS_HPP
#define PHYSICS_HPP
#include "SDL2/SDL_stdinc.h"
#include "macros/macro_utils.hpp"
#include "sprites.hpp"
#include <bitset>
#include <optional>

namespace Physics {
    struct Data {
        enum class Flags : Uint8 {
            Empty = 0,
            Gravity = BITOFFSET(0),
            Ghost = BITOFFSET(1),
        };
        friend constexpr ENUM_INT_TYPE(Flags) operator|(Flags a, Flags b) {
            return ENUM_TO_INT(a) | ENUM_TO_INT(b);
        }
        float ax = 0, ay = 0, vx = 0, vy = 0;
        using FlagSet = std::bitset<ENUM_SIZE(Flags) * 8>;
        FlagSet flags = Flags::Empty | Flags::Gravity;
    };
    void Register(Sprite::ID, Data::Flags);
    void UnRegister(Sprite::ID, Data::Flags);
    std::optional<Data>& Get(Sprite::ID);
    void Update();
}
#endif /* PHYSICS_HPP */
