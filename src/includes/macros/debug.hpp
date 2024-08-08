#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <print>
#include <exception> // IWYU pragma: keep
#include "macro_utils.hpp" // IWYU pragma: keep
#include "text_color.hpp" // IWYU pragma: keep
#define get_first_macro(x, ...) x
#ifdef DEBUG
#define DEBUG_COLOR_PRINT(colors, x, ...) do { \
    std::println(colors "FILE : " __FILE__ " | LINE : " stringify_macro(__LINE__) \
        " | FUNCTION : {}\n| MSG : " x RESET_C, \
        __PRETTY_FUNCTION__ __VA_OPT__(, __VA_ARGS__)); \
} while (0)
#define DEBUG_EXPAND(...) __VA_ARGS__
#define RELEASE_EXPAND(...)
#else
#define DEBUG_COLOR_PRINT(colors, x, ...) do { \
    std::println(colors "RELEASE LOG : " x, __VA_ARGS__); \
} while(0)
#define DEBUG_EXPAND(...)
#define RELEASE_EXPAND(...) __VA_ARGS__
#endif /* DEBUG */
#define DEBUG_LOG(...) DEBUG_COLOR_PRINT(GREEN_C, __VA_ARGS__)
#define DEBUG_WARN(...) DEBUG_COLOR_PRINT(YELLOW_C, __VA_ARGS__)
#define DEBUG_ERROR(...) do { \
    DEBUG_COLOR_PRINT(RED_C, __VA_ARGS__); \
    std::terminate(); \
} while(0)

#endif /* DEBUG_HPP */
