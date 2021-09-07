#pragma once

#include <ndv/vec.h>

#include <cmath>
#include <type_traits>

// shorthands for forcing vec functions for real (floating-point) types
// NOTE: some functions are not forced, however their behaviour may be of
// little use elsewhere
#define FORCE_REAL_TT typename std::enable_if_t<std::is_floating_point_v<T>, T>
#define FORCE_REAL_TNT typename std::enable_if_t<std::is_floating_point_v<T>, Vec<N, T>>
#define FORCE_REAL_TnT typename std::enable_if_t<std::is_floating_point_v<T>, Vec<n, T>>

namespace ndv
{
  template<int N, typename T>
  inline T length_squared(const Vec<N, T>& rhs)
  {
    T result = 0;
    for (int i = 0; i < N; i++)
      result += pow(rhs[i], 2);
    return result;
  }

  template<int N, typename T>
  inline FORCE_REAL_TT length(const Vec<N, T>& rhs)
  {
    return sqrt(length_squared(rhs));
  }

  template<int N, typename T>
  inline T distance_squared(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    return length_squared(lhs - rhs);
  }

  template<int N, typename T>
  inline FORCE_REAL_TT distance(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    return length(lhs - rhs);
  }

  template<int N, typename T>
  inline FORCE_REAL_TNT normalize(const Vec<N, T>& rhs)
  {
    T len = length(rhs);
    return (rhs / len);
  }

  template<int N, typename T>
  inline T dot(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    T result = 0;
    for (int i = 0; i < N; i++)
      result += lhs[i] * rhs[i];
    return result;
  }

  template<typename T>
  inline Vec<3, T> cross(const Vec<3, T>& lhs, const Vec<3, T>& rhs)
  {
    return Vec<3, T>(
      lhs.y * rhs.z - lhs.z * rhs.y,
      lhs.z * rhs.x - lhs.x * rhs.z,
      lhs.x * rhs.y - lhs.y * rhs.x
    );
  }

  template<int N, typename T>
  inline FORCE_REAL_TT angle(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    return acos(dot(lhs, rhs) / (length(lhs) * length(rhs)));
  }

  template<typename T>
  inline Vec<2, T> perpendicular(const Vec<2, T>& rhs)
  {
    return Vec<2, T>(
      -rhs.y,
      rhs.x
    );
  }

  template<int N, typename T>
  inline Vec<N, T> reflect(const Vec<N, T>& vi, const Vec<N, T>& vn)
  {
    return vi - (2 * dot(vn, vi) * vn);
  }

  template<int N, typename T>
  inline FORCE_REAL_TNT refract(const Vec<N, T>& vi, const Vec<N, T>& vn, T eta)
  {
    T cosI = -dot(vn, vi);
    return eta * vi + (eta * cosI - sqrt(1 - pow(eta, 2) * (1 - pow(cosI, 2)))) * vn;
  }

  template<int N, typename T>
  inline FORCE_REAL_TNT refract(const Vec<N, T>& vi, const Vec<N, T>& vn, T n1, T n2)
  {
    return refract(vi, vn, n1 / n2);
  }

  template<int N, typename T>
  inline Vec<N, T> faceforward(const Vec<N, T>& vi, const Vec<N, T>& vn, const Vec<N, T>& vref)
  {
    return (dot(vref, vi) < 0) ? vn : -vn;
  }
}