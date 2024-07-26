#ifndef LIST_MACROS_HPP
#define LIST_MACROS_HPP

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
#define list_size_macro(...) EXPAND(list_size_macro_h(__VA_ARGS__))
#define list_size_macro_h(x, ...) (1 __VA_OPT__( + list_size_macro_a PARENS (__VA_ARGS__)))
#define list_size_macro_a() list_size_macro_h

#endif /* LIST_MACROS_HPP */
