#pragma once

#include <ndv/vec.h>

#include <assert.h>
#include <cstdarg>
#include <type_traits>

#define ENABLE_REAL(T) typename std::enable_if_t<std::is_floating_point_v<T>>

namespace ndv
{
#pragma region "Quat Definitions"
  template<typename T, typename U=void>
  struct Quat;

  // allow Quat for floating-point types only
  template<typename T>
  struct Quat<T, ENABLE_REAL(T)>
  {
    union
    {
      struct
      {
        T w;
        union
        {
          struct { T x, y, z; };
          Vec<3, T> real;
        };
      };
      T data[4];
    };

    Quat() : w(1), x(0), y(0), z(0) {}
    Quat(const T& arg) : w(arg), x(arg), y(arg), z(arg) {}
    Quat(const T& w, const T& x, const T& y, const T& z) : w(w), x(x), y(y), z(z) {}
    Quat(const std::initializer_list<T> args);
    Quat(const Vec<3, T>& axis, const T& angle);
    
    T operator[](int i) const;
    T& operator[](int i);

    // Quat& operator=(const Quat& v);
    // Quat& operator+=(const Quat& v);
    // Quat& operator-=(const Quat& v);
    // Quat& operator*=(const Quat& v);
    // Quat& operator*=(const T& rhs);
    // Quat& operator/=(const Quat& v);
    // Quat& operator/=(const T& rhs);
  };
  using Quatf = Quat<float>;
  using Quatd = Quat<double>;

#pragma endregion
#pragma region "Base Methods"
  template<typename T>
  Quat<T, ENABLE_REAL(T)>::Quat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 4);
    int i = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
      data[i] = *it;
  }

  template<typename T>
  Quat<T, ENABLE_REAL(T)>::Quat(const Vec<3, T>& axis, const T& angle)
  {
    
  }

  template<typename T>
  T Quat<T, ENABLE_REAL(T)>::operator[](int i) const
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

  template<typename T>
  T& Quat<T, ENABLE_REAL(T)>::operator[](int i)
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

#pragma endregion
}