#pragma once

#include <ndv/vec.h>

#include <assert.h>
#include <cmath>
#include <cstdarg>
#include <type_traits>

// shorthand for forcing quaternions for real types
#define FORCE_REAL_T T, typename std::enable_if_t<std::is_floating_point_v<T>>

namespace ndv
{
#pragma region "Quat Definitions"
  template<typename T, typename U=void>
  struct Quat;

  // specialize Quat for floating-point types only
  template<typename T>
  struct Quat<FORCE_REAL_T>
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

    static const Quat identity;

    Quat() : w(1), x(0), y(0), z(0) {}
    Quat(T arg) : w(arg), x(arg), y(arg), z(arg) {}
    Quat(T w, T x, T y, T z) : w(w), x(x), y(y), z(z) {}
    Quat(const Vec<3, T>& real) : w(0) : x(x), y(y), z(z) {}
    Quat(const std::initializer_list<T> args);
    Quat(const Vec<3, T>& axis, T angle);
    
    T operator[](int i) const;
    T& operator[](int i);

    Quat& operator=(const Quat& rhs);
    Quat& operator*=(const Quat& rhs);
    Quat& operator*=(T rhs);
    Quat& operator/=(T rhs);
  };
  using Quatf = Quat<float>;
  using Quatd = Quat<double>;

#pragma endregion
#pragma region "Base Methods"
  template<typename T> const Quat<FORCE_REAL_T> Quat<FORCE_REAL_T>::identity = Quat(1, 0, 0, 0);

  template<typename T>
  inline Quat<FORCE_REAL_T>::Quat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 4);
    int i = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
      data[i] = *it;
  }

  template<typename T>
  inline Quat<FORCE_REAL_T>::Quat(const Vec<3, T>& axis, T angle)
  {
    w = cos(angle / T(2.0f)),
    real = sin(angle / T(2.0f)) * normalize(axis);
  }

  template<typename T>
  inline T Quat<FORCE_REAL_T>::operator[](int i) const
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

  template<typename T>
  inline T& Quat<FORCE_REAL_T>::operator[](int i)
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

  template<typename T>
  inline Quat<FORCE_REAL_T>& Quat<FORCE_REAL_T>::operator=(const Quat<FORCE_REAL_T>& rhs)
  {
    w = rhs.w;
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

  template<typename T>
  inline Quat<FORCE_REAL_T>& Quat<FORCE_REAL_T>::operator*=(const Quat<FORCE_REAL_T>& rhs)
  {
    w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    x = w * rhs.x - x * rhs.w - y * rhs.z - z * rhs.y;
    y = w * rhs.y - x * rhs.z - y * rhs.w - z * rhs.x;
    z = w * rhs.z - x * rhs.y - y * rhs.x - z * rhs.w;
    return *this;
  }

  template<typename T>
  inline Quat<FORCE_REAL_T>& Quat<FORCE_REAL_T>::operator*=(T rhs)
  {
    w *= rhs;
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  template<typename T>
  inline Quat<FORCE_REAL_T>& Quat<FORCE_REAL_T>::operator/=(T rhs)
  {
    w /= rhs;
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

  template<int N, typename T>
  inline Quat<T> operator+(const Quat<T>& rhs)
  {
    return rhs;
  }

  template<int N, typename T>
  inline Quat<T> operator-(const Quat<T>& rhs)
  {
    return Quat(
      -rhs.w,
      -rhs.x,
      -rhs.y,
      -rhs.z
    );
  }

  template<int N, typename T>
  inline Quat<T> operator*(const Quat<T>& lhs, const Quat<T>& rhs)
  {
    return Quat<T>(
      lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
      lhs.w * rhs.x - lhs.x * rhs.w - lhs.y * rhs.z - lhs.z * rhs.y,
      lhs.w * rhs.y - lhs.x * rhs.z - lhs.y * rhs.w - lhs.z * rhs.x,
      lhs.w * rhs.z - lhs.x * rhs.y - lhs.y * rhs.x - lhs.z * rhs.w
    );
  }

  template<int N, typename T>
  inline Quat<T> operator*(const Quat<T>& lhs, T rhs)
  {
    return Quat<T>(
      lhs.w * rhs,
      lhs.x * rhs,
      lhs.y * rhs,
      lhs.z * rhs
    );
  }

  template<int N, typename T>
  inline Quat<T> operator*(T lhs, const Quat<T>& rhs)
  {
    return Quat<T>(
      lhs * rhs.w,
      lhs * rhs.x,
      lhs * rhs.y,
      lhs * rhs.z
    );
  }

  template<int N, typename T>
  inline Quat<T> operator/(const Quat<T>& lhs, T rhs)
  {
    return Quat<T>(
      lhs.w / rhs,
      lhs.x / rhs,
      lhs.y / rhs,
      lhs.z / rhs
    );
  }

  template<int N, typename T>
  inline Quat<T> operator/(T lhs, const Quat<T>& rhs)
  {
    return Quat<T>(
      lhs / rhs.w,
      lhs / rhs.x,
      lhs / rhs.y,
      lhs / rhs.z
    );
  }

  template<int N, typename T>
  inline bool operator==(const Quat<T>& lhs, const Quat<T>& rhs)
  {
    return (
      lhs.w == rhs.w &&
      lhs.x == rhs.x &&
      lhs.y == rhs.y &&
      lhs.z == rhs.z
    );
  }

  template<int N, typename T>
  inline bool operator!=(const Quat<T>& lhs, const Quat<T>& rhs)
  {
    return (
      lhs.w != rhs.w ||
      lhs.x != rhs.x ||
      lhs.y != rhs.y ||
      lhs.z != rhs.z
    );
  }

#pragma endregion
#pragma region "Utility Methods"
template<typename T>
  inline T length_squared(const Quat<T>& rhs)
  {
    return w * rhs.w + x * rhs.x + y * rhs.y + z * rhs.z;
  }

  template<typename T>
  inline T length(const Quat<T>& rhs)
  {
    return sqrt(length_squared(rhs));
  }

  template<typename T>
  inline Quat<T> normalize(const Quat<T>& rhs)
  {
    return (rhs / length(rhs));
  }

  // fast half-quaternion
  template<typename T>
  inline Quat<T> half(const Quat<T>& rhs)
  {
    return normalize(Quat(w + 1, x, y, z));
  }

  template<typename T>
  inline T dot(const Quat<T>& lhs, const Quat<T>& rhs)
  {
    T result = 0;
    for (int i = 0; i < N; i++)
      result += lhs[i] * rhs[i];
    return result;
  }

  template<typename T>
  inline T cross(const Quat<T>& lhs, const Quat<T>& rhs)
  {
		return Quat<T>(
			lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
			lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x);
  }

  template<typename T>
  inline Quat<T> conjugate(const Quat<T>& rhs)
  {
    return Quat(
      rhs.w,
      -rhs.x,
      -rhs.y,
      -rhs.z
    );
  }

  template<typename T>
  inline Quat<T> inverse(const Quat<T>& rhs)
  {
    return (conjugate(rhs) / length(rhs));
  }

  // NOTE: quaternion must be normalized
  template<typename T>
  inline Vec<3, T> rotate(const Vec<3, T>& v, const Quat<T>& q)
  {
    Quat<T> out = q * Quat<T>(v) * q.conj();
    return out.real;
  }

  // template<typename T>
  // inline Quat<T> look_at(const Vec<3, T>& eye, const Vec<3, T>& target, const Vec<3, T>& up)
  // {
  //   Vec<3, T> f = normalize(target - eye); // forward vector
  //   Vec<3, T> r = normalize(cross(up, f)); // right axis
  //   Vec<3, T> u = cross(f, r); // rotated up

  //   Mat<3, 3, T> rot({
  //     {r.x, u.x, f.x},
  //     {r.y, u.y, f.y},
  //     {r.z, u.z, f.z}
  //   });
  //   // TODO: use Mat3x3
  //   // return Mat4::to_quat(rot);
  //   return Quat<T>::identity;
  // }

  template<typename T>
  inline Quat<T> look_at(const Vec<3, T>& eye, const Vec<3, T>& target)
  {
    return look_at(eye, target, Vec<3, T>::unit_y);
  }

  // NOTE: quaternion must be normalized
  template<typename T>
  inline Quat<T> slerp(const Quat<T>& q1, const Quat<T>& q2, T t)
  {
    T cos_th_2 = dot(q1, q2);
    int s = (cos_th_2 < 0.0f) ? -1 : 1; // shortest path from acos
    cos_th_2 *= s;

    T th_2 = acos(cos_th_2);
    T sin_th_2 = sqrt(1.0f - cos_th_2 * cos_th_2);
    
    T a, b;
    // theta approaches 180 degrees
    if (abs(sin_th_2) < 0.001f)
    {
      a = 0.5f;
      b = 0.5f;
    }
    else
    {
      a = sin((1 - t) * th_2) / sin_th_2;
      b = sin(t * th_2) / sin_th_2;
    }

    return ((a * q1) + ((s * b) * q2));
  }

  template<typename T>
  inline Quat<T> slerp_clamp(const Quat<T>& q1, const Quat<T>& q2, T t)
  {
    T tc = clamp(t, 0.0f, 1.0f);
    return slerp(q1, q2, tc);
  }

  template<typename T>
  inline Quat<T> nlerp(const Quat<T>& q1, const Quat<T>& q2, T t)
  {
    T cos_th_2 = dot(q1, q2);
    int s = (cos_th_2 < 0.0f) ? -1 : 1; // shortest path from acos
    return normalize((q1 * (1.0f - t)) + (q2 * (s * t)));
  }

  template<typename T>
  inline Quat<T> nlerp_clamp(const Quat<T>& q1, const Quat<T>& q2, T t)
  {
    T tc = clamp(t, 0.0f, 1.0f);
    return nlerp(q1, q2, tc);
  }

  template<typename T>
  inline Quat<T> squad(const Quat<T>& q1, const Quat<T>& q2, const Quat<T>& s1, const Quat<T>& s2, T t)
  {
    return slerp(slerp(q1, q2, t), slerp(s1, s2, t), 2 * t * (1 - t));
  }

  template<typename T>
  inline Quat<T> squad_clamp(const Quat<T>& q1, const Quat<T>& q2, const Quat<T>& s1, const Quat<T>& s2, T t)
  {
    T tc = clamp(t, 0.0f, 1.0f);
    return squad(q1, q2, s1, s2, tc);
  }

  // template<typename T>
  // inline Quat<T> spline(const Quat<T> seq[], int sz, T t)
  // {

  // }

  // template<typename T>
  // inline Quat<T> spline_clamp(const Quat<T> seq[], int sz, T t)
  // {

  // }

#pragma endregion
}