#ifndef DEBUG_HPP
#define DEBUG_HPP
#include "macro_utils.hpp" // IWYU pragma: keep
#include "text_color.hpp" // IWYU pragma: keep
#ifdef DEBUG
#include <print>
#include <exception>
#define get_first_macro(x, ...) x
#define DEBUG_COLOR_PRINT(colors, x, ...) do { \
    __VA_OPT__(auto expand_concat_macro(filler__dnu__macro__str__, __LINE__) = std::format(x , __VA_ARGS__);) \
    std::println(colors "FILE : {} | LINE : {} | FUNCTION : {} |\nMSG : {}" RESET_C, \
        __FILE__, __LINE__, __PRETTY_FUNCTION__, get_first_macro(__VA_OPT__(expand_concat_macro(filler__dnu__macro__str__, __LINE__) ,) x)); \
} while (0)
#define DEBUG_LOG(...) DEBUG_COLOR_PRINT(GREEN_C, __VA_ARGS__)
#define DEBUG_WARN(...) DEBUG_COLOR_PRINT(YELLOW_C, __VA_ARGS__)
#define DEBUG_ERROR(...) do { \
    DEBUG_COLOR_PRINT(RED_C, __VA_ARGS__); \
    std::terminate(); \
} while(0)
#define DEBUG_EXPAND(...) __VA_ARGS__
#else
#define DEBUG_COLOR_PRINT(...)
#define DEBUG_LOG(...)
#define DEBUG_WARN(...)
#define DEBUG_ERROR(...)
#define DEBUG_EXPAND(...)
#endif /* DEBUG */

#endif /* DEBUG_HPP */
