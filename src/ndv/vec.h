#pragma once

#include <assert.h>
#include <cstdarg>

#include <array>

namespace bones
{
#pragma region "Vec Definitions"
  template<int N, typename T>
  struct Vec
  {
    T data[N];

    Vec() = default;
    Vec(const T& arg);
    Vec(const std::initializer_list<T> args);

    T operator[](int i) const;
    T& operator[](int i);

    Vec& operator=(const Vec& v);
    Vec& operator+=(const Vec& v);
    Vec& operator-=(const Vec& v);
    Vec& operator*=(const Vec& v);
    Vec& operator*=(const T& rhs);
    Vec& operator/=(const Vec& v);
    Vec& operator/=(const T& rhs);
  };
  
  template <typename T>
  struct Vec<2, T>
  {
    union
    {
      struct { T x, y; };
      T data[2];
    };

    static const Vec zero;
    static const Vec one;
    static const Vec unit_x;
    static const Vec unit_y;

    Vec() = default;
    Vec(const T& arg) : x(arg), y(arg) {}
    Vec(const std::initializer_list<T> args);
    Vec(const T& x, const T& y) : x(x), y(y) {}

    T operator[](int i) const;
    T& operator[](int i);

    Vec& operator=(const Vec& v);
    Vec& operator+=(const Vec& v);
    Vec& operator-=(const Vec& v);
    Vec& operator*=(const Vec& v);
    Vec& operator*=(const T& rhs);
    Vec& operator/=(const Vec& v);
    Vec& operator/=(const T& rhs);
  };
  using Vec2i = Vec<2, int>;
  using Vec2f = Vec<2, float>;
  using Vec2d = Vec<2, double>;

  template <typename T>
  struct Vec<3, T>
  {
    union
    {
      struct { T x, y, z; };
      T data[3];
    };

    static const Vec zero;
    static const Vec one;
    static const Vec unit_x;
    static const Vec unit_y;
    static const Vec unit_z;

    Vec() = default;
    Vec(const T& arg) : x(arg), y(arg), z(arg) {}
    Vec(const std::initializer_list<T> args);
    Vec(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

    T operator[](int i) const;
    T& operator[](int i);

    Vec& operator=(const Vec& v);
    Vec& operator+=(const Vec& v);
    Vec& operator-=(const Vec& v);
    Vec& operator*=(const Vec& v);
    Vec& operator*=(const T& rhs);
    Vec& operator/=(const Vec& v);
    Vec& operator/=(const T& rhs);
  };
  using Vec3i = Vec<3, int>;
  using Vec3f = Vec<3, float>;
  using Vec3d = Vec<3, double>;

  template <typename T>
  struct Vec<4, T>
  {
    union
    {
      struct { T x, y, z, w; };
      T data[4];
    };

    Vec() = default;
    Vec(const T& arg) : x(arg), y(arg), z(arg), w(arg) {}
    Vec(const std::initializer_list<T> args);
    Vec(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}

    T operator[](int i) const;
    T& operator[](int i);

    Vec& operator=(const Vec& v);
    Vec& operator+=(const Vec& v);
    Vec& operator-=(const Vec& v);
    Vec& operator*=(const Vec& v);
    Vec& operator*=(const T& rhs);
    Vec& operator/=(const Vec& v);
    Vec& operator/=(const T& rhs);
  };
  using Vec4i = Vec<4, int>;
  using Vec4f = Vec<4, float>;
  using Vec4d = Vec<4, double>;

#pragma endregion
#pragma region "Base Methods"
  template<int N, typename T>
  inline Vec<N, T>::Vec(const T& arg)
  {
    for (int i = 0; i < N; i++)
      data[i] = arg;
  }

  template<int N, typename T>
  inline Vec<N, T>::Vec(const std::initializer_list<T> args)
  {
    assert(args.size() <= N);
    int i = 0;
    for (auto it = args.begin(); it != args.end() && i < N; ++it)
      data[i++] = *it;
  }

  template<int N, typename T>
  inline T Vec<N, T>::operator[](int i) const
  {
    assert(i >= 0 && i < N);
    return data[i];
  }

  template<int N, typename T>
  inline T& Vec<N, T>::operator[](int i)
  {
    assert(i >= 0 && i < N);
    return data[i];
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] = rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator+=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] += rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator-=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] -= rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator*=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] *= rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator*=(const T& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] *= rhs;
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator/=(const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] /= rhs[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator/=(const T& rhs)
  {
    for (int i = 0; i < N; i++)
      data[i] /= rhs;
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T> operator+(const Vec<N, T>& rhs)
  {
    return v;
  }

  template<int N, typename T>
  inline Vec<N, T> operator-(const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = -rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator+(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] + rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator-(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] - rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator*(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] * rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator*(const Vec<N, T>& lhs, const T& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] * rhs;
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator*(const T& lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs * rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator/(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] / rhs[i];
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator/(const Vec<N, T>& lhs, const T& rhs)
  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs[i] / rhs;
    return result;
  }

  template<int N, typename T>
  inline Vec<N, T> operator/(const T& lhs, const Vec<N, T>& rhs)

  {
    Vec<N, T> result;
    for (int i = 0; i < N; i++)
      result[i] = lhs / rhs[i];
    return result;
  }

  template<int N, typename T>
  inline bool operator==(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      if (lhs[i] != rhs[i])
        return false;
    return true;
  }

  template<int N, typename T>
  inline bool operator!=(const Vec<N, T>& lhs, const Vec<N, T>& rhs)
  {
    for (int i = 0; i < N; i++)
      if (lhs[i] != rhs[i])
        return true;
    return false;
  }

#pragma endregion
#pragma region "Vec2 Methods"
  template<typename T>
  inline Vec<2, T>::Vec(const std::initializer_list<T> args)
  {
    assert(args.size() <= 2);
    int i = 0;
    for (auto it = args.begin(); it != args.end() && i < 2; ++it)
      data[i++] = *it;
  }

  template<typename T> const Vec<2, T> Vec<2, T>::zero = Vec<2, T>(0);
  template<typename T> const Vec<2, T> Vec<2, T>::one = Vec<2, T>(1);
  template<typename T> const Vec<2, T> Vec<2, T>::unit_x = Vec<2, T>(1, 0);
  template<typename T> const Vec<2, T> Vec<2, T>::unit_y = Vec<2, T>(0, 1);

  template<typename T>
  inline T Vec<2, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 2);
    return data[i];
  }

  template<typename T>
  inline T& Vec<2, T>::operator[](int i)
  {
    assert(i >= 0 && i < 2);
    return data[i];
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator=(const Vec<2, T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator+=(const Vec<2, T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator-=(const Vec<2, T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator*=(const Vec<2, T>& rhs)
  {
    x *= rhs.x;
    y *= rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator*=(const T& rhs)
  {
    x *= s;
    y *= s;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator/=(const Vec<2, T>& rhs)
  {
    x /= rhs.x;
    y /= rhs.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator/=(const T& rhs)
  {
    x /= s;
    y /= s;
    return *this;
  }

#pragma endregion
#pragma region "Vec3 Methods"
  template<typename T>
  inline Vec<3, T>::Vec(const std::initializer_list<T> args)
  {
    // NOTE: we could allow larger lists (with truncation)
    assert(args.size() <= 3);
    int i = 0;
    for (auto it = args.begin(); it != args.end() && i < 3; ++it)
      data[i++] = *it;
  }

  template<typename T> const Vec<3, T> Vec<3, T>::zero = Vec<3, T>(0);
  template<typename T> const Vec<3, T> Vec<3, T>::one = Vec<3, T>(1);
  template<typename T> const Vec<3, T> Vec<3, T>::unit_x = Vec<3, T>(1, 0, 0);
  template<typename T> const Vec<3, T> Vec<3, T>::unit_y = Vec<3, T>(0, 1, 0);
  template<typename T> const Vec<3, T> Vec<3, T>::unit_z = Vec<3, T>(0, 0, 1);

  template<typename T>
  inline T Vec<3, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 3);
    return data[i];
  }

  template<typename T>
  inline T& Vec<3, T>::operator[](int i)
  {
    assert(i >= 0 && i < 3);
    return data[i];
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator=(const Vec<3, T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator+=(const Vec<3, T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator-=(const Vec<3, T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator*=(const Vec<3, T>& rhs)
  {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator*=(const T& rhs)
  {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator/=(const Vec<3, T>& rhs)
  {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator/=(const T& rhs)
  {
    x /= s;
    y /= s;
    z /= s;
    return *this;
  }

#pragma endregion
#pragma region "Vec4 Methods"
  template<typename T>
  inline Vec<4, T>::Vec(const std::initializer_list<T> args)
  {
    // NOTE: we could allow larger lists (with truncation)
    assert(args.size() <= 4);
    int i = 0;
    for (auto it = args.begin(); it != args.end() && i < 4; ++it)
      data[i++] = *it;
  }

  template<typename T>
  inline T Vec<4, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

  template<typename T>
  inline T& Vec<4, T>::operator[](int i)
  {
    assert(i >= 0 && i < 4);
    return data[i];
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator=(const Vec<4, T>& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator+=(const Vec<4, T>& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator-=(const Vec<4, T>& rhs)
  {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator*=(const Vec<4, T>& rhs)
  {
    x *= rhs.x;
    y *= rhs.y;
    z *= rhs.z;
    w *= rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator*=(const T& rhs)
  {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator/=(const Vec<4, T>& rhs)
  {
    x /= rhs.x;
    y /= rhs.y;
    z /= rhs.z;
    w /= rhs.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator/=(const T& rhs)
  {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
  }

#pragma endregion
}