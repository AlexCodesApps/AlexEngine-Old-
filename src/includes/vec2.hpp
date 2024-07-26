#pragma once
#include <cmath>

struct Vec2 {
private:
public:
    float x, y;
    float magnitude() {
        return std::sqrt(x * x + y * y);
    }
};
