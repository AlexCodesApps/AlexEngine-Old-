#ifndef DEFER_HPP
#define DEFER_HPP
#include "macro_utils.hpp"
struct defer_function_call_t {};
#define DEFER_CALL(x, ...) \
namespace detail {static defer_function_call_t unique_name_macro = [](){x(__VA_ARGS__); return defer_function_call_t{};}();}
#endif /* DEFER_HPP */
