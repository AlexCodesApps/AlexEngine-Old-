#ifndef MACRO_UTILS_HPP
#define MACRO_UTILS_HPP
#include "warning_ignore.hpp"
WARNING_IGNORE_HEADER(-Weverything)
#include <climits>
#include <type_traits> // IWYU pragma: keep
WARNING_IGNORE_TAIL
#define enumerate_macro(name, ...) enum class name {__VA_ARGS__};
#define BITOFFSET(x) (1 << x)
#define ENUM_INT_TYPE(e) std::underlying_type_t<e>
#define ENUM_TO_INT(e) static_cast<ENUM_INT_TYPE(decltype(e))>(e)
#define ENUM_SIZE(e) sizeof(ENUM_INT_TYPE(e))

#define concat_macro(x, y) x ## y
#define expand_concat_macro(x, y) concat_macro(x,y)
#define unique_name_macro expand_concat_macro(filler__dnu__macro__, __COUNTER__)
// #ifndef _
// #define _ unique_name_macro
// #endif /* _ */
#define lambda_body_macro_h(...) {return __VA_ARGS__;}
#define lambda_arg_macro_h(x) auto&& x
#define lambda_macro(...) [=](__VA_OPT__(map_macro(lambda_arg_macro_h, __VA_ARGS__))) lambda_body_macro_h
#define stringify_macro_h(x) #x
#define stringify_macro(x) stringify_macro_h(x)
#define BYTE_SIZE CHAR_BIT

#endif /* MACRO_UTILS_HPP */
