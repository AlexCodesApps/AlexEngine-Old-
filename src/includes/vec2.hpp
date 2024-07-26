#pragma once
#include "intalias.hpp"
#include <cmath>

struct Vec2 {
private:
public:
    f32 x, y;
    f32 magnitude() {
        return std::sqrt(x * x + y * y);
    }
};
