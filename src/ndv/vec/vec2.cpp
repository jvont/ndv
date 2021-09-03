#include <ndv/vec/vec2.h>

#pragma region "Vec2 Base"
template<typename T>
Vec2Base<T>& Vec2Base<T>::operator+=(const Vec2Base<T>& v)
{
  x += v.x;
  y += v.y;
  return *this;
}

#pragma endregion
#pragma region "Vec2 Real"
template<typename T>
T Vec2<T, ENABLE_REAL(T)>::norm() const
{
  return (this->x * this->x + this->y * this->y);
}

#pragma endregion

template struct Vec2Base<int>;
template struct Vec2Base<float>;
template struct Vec2Base<double>;

template struct Vec2<int>;
template struct Vec2<float>;
template struct Vec2<double>;