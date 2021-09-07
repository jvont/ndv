#pragma once

#include <ndv/vec.h>

#include <assert.h>
#include <cstdarg>
#include <type_traits>

#define ENABLE_REAL_T T, typename std::enable_if<std::is_floating_point<T>::value>::type

namespace ndv
{
#pragma region "Quat Definitions"
  template<typename T, typename U=void>
  struct Quat;

  // specialize Quat for floating-point types only
  template<typename T>
  struct Quat<ENABLE_REAL_T>
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

    Quat& operator=(const Quat& rhs);
    Quat& operator*=(const Quat& rhs);
  };
  using Quatf = Quat<float>;
  using Quatd = Quat<double>;

#pragma endregion
#pragma region "Base Methods"
  template<typename T>
  inline Quat<ENABLE_REAL_T>::Quat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 4);
    int i = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
      data[i] = *it;
  }

  template<typename T>
  inline Quat<ENABLE_REAL_T>::Quat(const Vec<3, T>& axis, const T& angle)
  {
    // Vec3 n_axis = normalize(axis);
    // float sin_angle_2 = sin(angle / 2.0f);
    // return Quat(
    //   cos(angle / T(2.0f)),
    //   n_axis.x * sin_angle_2,
    //   n_axis.y * sin_angle_2,
    //   n_axis.z * sin_angle_2
    // );
  }

  template<typename T>
  inline T Quat<ENABLE_REAL_T>::operator[](int i) const
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

  template<typename T>
  inline T& Quat<ENABLE_REAL_T>::operator[](int i)
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

  template<typename T>
  inline Quat<ENABLE_REAL_T>& Quat<ENABLE_REAL_T>::operator=(const Quat<ENABLE_REAL_T>& rhs)
  {
    w = rhs.w;
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

  template<typename T>
  inline Quat<ENABLE_REAL_T>& Quat<ENABLE_REAL_T>::operator*=(const Quat<ENABLE_REAL_T>& rhs)
  {
    w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    x = w * rhs.x - x * rhs.w - y * rhs.z - z * rhs.y;
    y = w * rhs.y - x * rhs.z - y * rhs.w - z * rhs.x;
    z = w * rhs.z - x * rhs.y - y * rhs.x - z * rhs.w;
    return *this;
  }

  template<int N, typename T>
  inline Quat<ENABLE_REAL_T> operator+(const Quat<ENABLE_REAL_T>& rhs)
  {
    return rhs;
  }

  template<int N, typename T>
  inline Quat<ENABLE_REAL_T> operator-(const Quat<ENABLE_REAL_T>& rhs)
  {
    return Quat(
      -rhs.w,
      -rhs.x,
      -rhs.y,
      -rhs.z
    );
  }

  template<int N, typename T>
  inline Quat<ENABLE_REAL_T> operator*(const Quat<ENABLE_REAL_T>& lhs, const Quat<ENABLE_REAL_T>& rhs)
  {
    Quat<T> result;
    result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
    result.x = lhs.w * rhs.x - lhs.x * rhs.w - lhs.y * rhs.z - lhs.z * rhs.y;
    result.y = lhs.w * rhs.y - lhs.x * rhs.z - lhs.y * rhs.w - lhs.z * rhs.x;
    result.z = lhs.w * rhs.z - lhs.x * rhs.y - lhs.y * rhs.x - lhs.z * rhs.w;
    return result;
  }

  template<int N, typename T>
  inline bool operator==(const Quat<ENABLE_REAL_T>& lhs, const Quat<ENABLE_REAL_T>& rhs)
  {
    return (
      lhs.w == rhs.w &&
      lhs.x == rhs.x &&
      lhs.y == rhs.y &&
      lhs.z == rhs.z
    );
  }

  template<int N, typename T>
  inline bool operator!=(const Quat<ENABLE_REAL_T>& lhs, const Quat<ENABLE_REAL_T>& rhs)
  {
    return (
      lhs.w != rhs.w ||
      lhs.x != rhs.x ||
      lhs.y != rhs.y ||
      lhs.z != rhs.z
    );
  }

#pragma endregion
}