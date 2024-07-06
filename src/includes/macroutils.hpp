#pragma once
#define DO_PRAGMA(x) _Pragma(#x)
#ifdef __clang__
#define PRAGMA_DIAGNOSTIC(x) DO_PRAGMA(clang diagnostic x)
#elifdef __GNUC__
#define PRAGMA_DIAGNOSTIC(x) DO_PRAGMA(GCC diagnostic x)
#endif
#define WARNING_IGNORE(type) \
PRAGMA_DIAGNOSTIC(push) \
PRAGMA_DIAGNOSTIC(ignored #type) \
WARNING_IGNORE_BODY
#define WARNING_IGNORE_BODY(...) \
__VA_ARGS__ \
PRAGMA_DIAGNOSTIC(pop)
#include <climits>
#include <type_traits>
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
#define map_macro_h(macro, a, ...) macro(a) \
__VA_OPT__(, map_macro_a PARENS (macro, __VA_ARGS__))
#define map_macro(macro, ...) EXPAND(map_macro_h(macro, __VA_ARGS__))
#define map_macro_a() map_macro_h
#define enumerate_macro(name, ...) enum class name {__VA_ARGS__};
#define BITOFFSET(x) (1 << x)
#define ENUM_INT(e) std::underlying_type_t<e>
#define ENUM_TO_NUMBER(e) static_cast<ENUM_INT(decltype(e))>(e)
#define ENUM_SIZE(e) sizeof(ENUM_INT(e))
#define BLACK_C "\e[0;30m"
#define RED_C "\e[0;31m"
#define YELLOW_C "\e[0;33m"
#define YELLOW_CB "\e[43m"
#define GREEN_C "\e[0;32m"
#define RESET_C "\e[0m"
#ifdef DEBUG
#include <print>
#include <exception>
#define DEBUG_COLOR_PRINT(colors, x, ...) do { \
    auto expand_concat_macro(filler__dnu__macro__str__, __LINE__) = std::format(x __VA_OPT__(, __VA_ARGS__)); \
    std::println(colors "FILE : {} LINE : {} MSG : {}" RESET_C, \
        __FILE__, __LINE__, expand_concat_macro(filler__dnu__macro__str__, __LINE__)); \
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
#define concat_macro(x, y) x ## y
#define expand_concat_macro(x, y) concat_macro(x,y)
#define unique_name_macro expand_concat_macro(filler__dnu__macro__, __COUNTER__)
// #ifndef _
// #define _ unique_name_macro
// #endif /* _ */
#define lambda_body_macro_h(...) {return __VA_ARGS__;}
#define lambda_arg_macro_h(x) auto&& x
#define lambda_macro(...) [=](__VA_OPT__(map_macro(lambda_arg_macro_h, __VA_ARGS__))) lambda_body_macro_h
#define stringify_macro(x) #x
#define BYTE_SIZE CHAR_BIT
#define list_size_macro(...) EXPAND(list_size_macro_h(__VA_ARGS__))
#define list_size_macro_h(x, ...) (1 __VA_OPT__( + list_size_macro_a PARENS (__VA_ARGS__)))
#define list_size_macro_a() list_size_macro_h
