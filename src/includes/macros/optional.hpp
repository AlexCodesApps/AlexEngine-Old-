#define FIRST(x, ...) x
#define optional_macro(x, ...) FIRST(__VA_ARGS__ __VA_OPT__(,) x)
