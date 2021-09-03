#pragma once

#include <type_traits>

#define ENABLE_REAL(T) typename std::enable_if_t<std::is_floating_point_v<T>>