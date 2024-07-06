#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

template  <typename T>
std::tuple<float, float> float_pair_conversion(T&& value) {
    auto& [x, y] = value;
    static_assert(std::is_same_v<float, decltype(x)>, "Vec2 First Param Ilformed");
    static_assert(std::is_same_v<float, decltype(y)>, "Vec2 Second Param Ilformed");
    return {x, y};
}
struct v_t {};
static constexpr v_t x_t;
static constexpr v_t y_t;
struct Vec2 {
private:
public:
    float x, y;
    Vec2() = default;
    template<typename T>
    Vec2(T&& v) {
        auto& [sx, sy] = v;
        x = sx; y = sy;
    }
    Vec2(float x, float y)
    : x(x), y(y) {}
    Vec2(v_t, float y)
    : x(0), y(y) {}
    Vec2(float x, v_t)
    : x(x), y(0) {}
    template <typename T>
    requires (std::is_same_v<decltype(float_pair_conversion(std::declval<T>())), std::tuple<float, float>>)
    operator T&() {
        return *reinterpret_cast<T*>(this);
    }
};
