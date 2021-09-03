#pragma once

#include <ndv/vec/vec2.h>
#include <ndv/template_utils.h>

#include <array>

#pragma region "Vec2 Base"
template<typename T>
struct Vec2Base
{
  T x, y;
  Vec2Base(T x, T y) : x(x), y(y) {}

  Vec2Base& operator+=(const Vec2Base& v);
};

template<typename T, typename Flag=void>
struct Vec2 : public Vec2Base<T>
{
  using Vec2Base<T>::Vec2Base;
};

template<typename T>
Vec2Base<T> operator+(const Vec2Base<T>& v1, const Vec2Base<T>& v2);

#pragma endregion
#pragma region "Vec2 Real"
template<typename T>
struct Vec2<T, ENABLE_REAL(T)> : public Vec2Base<T>
{
  using Vec2Base<T>::Vec2Base;

  T norm() const;
};
#pragma endregion