#pragma once

#include <type_traits>

// from: https://stackoverflow.com/questions/11761703/overloading-macro-on-number-of-arguments

#define EXPAND( x ) x
#define GET_MACRO_2(_1,_2,NAME,...) NAME

#define ENABLE_REAL_1(T) typename std::enable_if_t<std::is_floating_point_v<T>>
#define ENABLE_REAL_2(T, Ret) typename std::enable_if_t<std::is_floating_point_v<T>, Ret>
#define ENABLE_REAL(...) EXPAND(GET_MACRO_2(__VA_ARGS__, ENABLE_REAL_2, ENABLE_REAL_1)(__VA_ARGS__))

#define ENABLE_INT_1(T) typename std::enable_if_t<std::is_integral_v<T>>
#define ENABLE_INT_2(T, Ret) typename std::enable_if_t<std::is_integral_v<T>, Ret>
#define ENABLE_INT(...) EXPAND(GET_MACRO_2(__VA_ARGS__, ENABLE_INT_2, ENABLE_INT_1)(__VA_ARGS__))