#pragma once
#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define PARENS ()
#define for_each_macro_h(macro, a, ...) macro(a) \
__VA_OPT__(for_each_macro_a PARENS (macro, __VA_ARGS__))
#define for_each_macro_a() for_each_macro_h
#define for_each_macro(macro, ...) EXPAND(for_each_macro_h(macro, __VA_ARGS__))
#define comma_h(x) x,
#define enumerate(name, ...) enum class name {for_each_macro(comma_h, __VA_ARGS__)};
#define BITOFFSET(x) 1 << x
#define ENUM_TO_NUMBER(e) \
static_cast<typename std::underlying_type<decltype(e)>::type>(e)
#define BLACK_C "\e[0;30m"
#define RED_C "\e[0;31m"
#define YELLOW_C "\e[0;33m"
#define YELLOW_CB "\e[43m"
#define GREEN_C "\e[0;32m"
#define RESET_C "\e[0m"
#ifdef DEBUG
#include <exception>
#define DEBUG_COLOR_PRINT(x, colors) \
std::println(colors "FILE : {} LINE : {} MSG : {}" RESET_C, __FILE__, __LINE__, x)
#define DEBUG_LOG(x) DEBUG_COLOR_PRINT(x, GREEN_C)
#define DEBUG_WARN(x) DEBUG_COLOR_PRINT(x, YELLOW_C)
#define DEBUG_ERROR(x) do { \
    DEBUG_COLOR_PRINT(x, RED_C); \
    std::terminate(); \
} while(0)
#else
#define DEBUG_COLOR_PRINT
#define DEBUG_LOG
#define DEBUG_WARN
#define DEBUG_ERROR
#endif /* DEBUG */
