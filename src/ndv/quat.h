#pragma once

#include <ndv/mat.h>
#include <ndv/vec.h>

#include <assert.h>
#include <cmath>
// #include <cstdarg>
// #include <type_traits>

namespace ndv
{
#pragma region "Quat Definitions"
  struct Quat
  {
    float w;
    union
    {
      struct { float x, y, z; };
      Vec<3, float> real;
    };

    static const Quat identity;

    Quat() : w(1), x(0), y(0), z(0) {}
    Quat(float arg) : w(arg), x(arg), y(arg), z(arg) {}
    Quat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}
    Quat(const Vec<3, float>& axis, float angle);
    explicit Quat(const Vec<3, float>& real) : w(0) , real(real) {}

    Quat& operator=(const Quat& rhs);
    Quat& operator+=(const Quat& rhs);
    Quat& operator-=(const Quat& rhs);
    Quat& operator*=(const Quat& rhs);
    Quat& operator*=(float rhs);
    Quat& operator/=(float rhs);
  };

#pragma endregion
#pragma region "Base Methods"
  const Quat Quat::identity = Quat(1, 0, 0, 0);

  inline Quat::Quat(const Vec<3, float>& axis, float angle)
  {
    w = cos(angle / float(2.0f)),
    real = sin(angle / float(2.0f)) * normalize(axis);
  }

  inline Quat& Quat::operator=(const Quat& rhs)
  {
    w = rhs.w;
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

  inline Quat& Quat::operator+=(const Quat& rhs)
  {
    w += rhs.w;
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  inline Quat& Quat::operator-=(const Quat& rhs)
  {
    w -= rhs.w;
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  inline Quat& Quat::operator*=(const Quat& rhs)
  {
    w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    x = w * rhs.x - x * rhs.w - y * rhs.z - z * rhs.y;
    y = w * rhs.y - x * rhs.z - y * rhs.w - z * rhs.x;
    z = w * rhs.z - x * rhs.y - y * rhs.x - z * rhs.w;
    return *this;
  }

  inline Quat& Quat::operator*=(float rhs)
  {
    w *= rhs;
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
  }

  inline Quat& Quat::operator/=(float rhs)
  {
    w /= rhs;
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
  }

  inline Quat operator+(const Quat& rhs)
  {
    return rhs;
  }

  inline Quat operator-(const Quat& rhs)
  {
    return Quat(
      -rhs.w,
      -rhs.x,
      -rhs.y,
      -rhs.z
    );
  }

  inline Quat operator+(const Quat& lhs, const Quat& rhs)
  {
    return Quat(
      lhs.w + rhs.w,
      lhs.x + rhs.x,
      lhs.y + rhs.y,
      lhs.z + rhs.z
    );
  }

  inline Quat operator-(const Quat& lhs, const Quat& rhs)
  {
    return Quat(
      lhs.w * rhs.w,
      lhs.x * rhs.x,
      lhs.y * rhs.y,
      lhs.z * rhs.z
    );
  }

  inline Quat operator*(const Quat& lhs, const Quat& rhs)
  {
    return Quat(
      lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
      lhs.w * rhs.x - lhs.x * rhs.w - lhs.y * rhs.z - lhs.z * rhs.y,
      lhs.w * rhs.y - lhs.x * rhs.z - lhs.y * rhs.w - lhs.z * rhs.x,
      lhs.w * rhs.z - lhs.x * rhs.y - lhs.y * rhs.x - lhs.z * rhs.w
    );
  }

  inline Quat operator*(const Quat& lhs, float rhs)
  {
    return Quat(
      lhs.w * rhs,
      lhs.x * rhs,
      lhs.y * rhs,
      lhs.z * rhs
    );
  }

  inline Quat operator*(float lhs, const Quat& rhs)
  {
    return Quat(
      lhs * rhs.w,
      lhs * rhs.x,
      lhs * rhs.y,
      lhs * rhs.z
    );
  }

  inline Quat operator/(const Quat& lhs, float rhs)
  {
    return Quat(
      lhs.w / rhs,
      lhs.x / rhs,
      lhs.y / rhs,
      lhs.z / rhs
    );
  }

  inline Quat operator/(float lhs, const Quat& rhs)
  {
    return Quat(
      lhs / rhs.w,
      lhs / rhs.x,
      lhs / rhs.y,
      lhs / rhs.z
    );
  }

  inline bool operator==(const Quat& lhs, const Quat& rhs)
  {
    return (
      lhs.w == rhs.w &&
      lhs.x == rhs.x &&
      lhs.y == rhs.y &&
      lhs.z == rhs.z
    );
  }

  inline bool operator!=(const Quat& lhs, const Quat& rhs)
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
  inline float length_squared(const Quat& rhs)
  {
    return rhs.w * rhs.w + rhs.x * rhs.x + rhs.y * rhs.y + rhs.z * rhs.z;
  }

  inline float length(const Quat& rhs)
  {
    return sqrt(length_squared(rhs));
  }

  inline Quat normalize(const Quat& rhs)
  {
    return (rhs / length(rhs));
  }

  // fast half-quaternion
  inline Quat half(const Quat& rhs)
  {
    return normalize(Quat(rhs.w + 1, rhs.x, rhs.y, rhs.z));
  }

  inline float dot(const Quat& lhs, const Quat& rhs)
  {
    return (lhs.w * rhs.w + lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
  }

  inline Quat cross(const Quat& lhs, const Quat& rhs)
  {
		return Quat(
			lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z,
			lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x
    );
  }

  inline Quat conjugate(const Quat& rhs)
  {
    return Quat(
      rhs.w,
      -rhs.x,
      -rhs.y,
      -rhs.z
    );
  }

  inline Quat inverse(const Quat& rhs)
  {
    return (conjugate(rhs) / length(rhs));
  }

  // NOTE: quaternion must be normalized
  inline Vec<3, float> rotate(const Vec<3, float>& v, const Quat& q)
  {
    return (q * Quat(v) * conjugate(q)).real;
  }

  // // inline Quat look_at(const Vec<3, float>& eye, const Vec<3, float>& target, const Vec<3, float>& up)
  // {
  //   Vec<3, float> f = normalize(target - eye); // forward vector
  //   Vec<3, float> r = normalize(cross(up, f)); // right axis
  //   Vec<3, float> u = cross(f, r); // rotated up

  //   Mat<3, 3, float> rot({
  //     {r.x, u.x, f.x},
  //     {r.y, u.y, f.y},
  //     {r.z, u.z, f.z}
  //   });
  //   // TODO: use Mat3x3
  //   // return Mat4::to_quat(rot);
  //   return Quat::identity;
  // }

  // // inline Quat look_at(const Vec<3, float>& eye, const Vec<3, float>& target)
  // {
  //   return look_at(eye, target, Vec<3, float>::unit_y);
  // }

  // NOTE: quaternion must be normalized
  inline Quat slerp(const Quat& q1, const Quat& q2, float t)
  {
    float cos_th_2 = dot(q1, q2);
    int s = (cos_th_2 < 0.0f) ? -1 : 1; // shortest path from acos
    cos_th_2 *= s;

    float th_2 = acos(cos_th_2);
    float sin_th_2 = sqrt(1.0f - cos_th_2 * cos_th_2);
    
    float a, b;
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

  // inline Quat slerp_clamp(const Quat& q1, const Quat& q2, float t)
  // {
  //   float tc = clamp(t, 0.0f, 1.0f);
  //   return slerp(q1, q2, tc);
  // }

  inline Quat nlerp(const Quat& q1, const Quat& q2, float t)
  {
    float cos_th_2 = dot(q1, q2);
    int s = (cos_th_2 < 0.0f) ? -1 : 1; // shortest path from acos
    return normalize((q1 * (1.0f - t)) + (q2 * (s * t)));
  }

  // inline Quat nlerp_clamp(const Quat& q1, const Quat& q2, float t)
  // {
  //   float tc = clamp(t, 0.0f, 1.0f);
  //   return nlerp(q1, q2, tc);
  // }

  inline Quat squad(const Quat& q1, const Quat& q2, const Quat& s1, const Quat& s2, float t)
  {
    return slerp(slerp(q1, q2, t), slerp(s1, s2, t), 2 * t * (1 - t));
  }

  // inline Quat squad_clamp(const Quat& q1, const Quat& q2, const Quat& s1, const Quat& s2, float t)
  // {
  //   float tc = clamp(t, 0.0f, 1.0f);
  //   return squad(q1, q2, s1, s2, tc);
  // }

  // // inline Quat spline(const Quat seq[], int sz, float t)
  // {

  // }

  // // inline Quat spline_clamp(const Quat seq[], int sz, float t)
  // {

  // }

#pragma endregion
}