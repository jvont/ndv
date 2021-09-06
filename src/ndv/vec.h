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
    Vec& operator*=(const T& s);
    Vec& operator/=(const Vec& v);
    Vec& operator/=(const T& s);
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
    Vec& operator*=(const T& s);
    Vec& operator/=(const Vec& v);
    Vec& operator/=(const T& s);
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
    Vec& operator*=(const T& s);
    Vec& operator/=(const Vec& v);
    Vec& operator/=(const T& s);
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
    Vec& operator*=(const T& s);
    Vec& operator/=(const Vec& v);
    Vec& operator/=(const T& s);
  };
  using Vec4i = Vec<4, int>;
  using Vec4f = Vec<4, float>;
  using Vec4d = Vec<4, double>;

#pragma endregion
#pragma region "Base Methods"
  template<int N, typename T>
  inline Vec<N, T>::Vec(const T& arg)
  {
    for (const auto& d : data)
      d = arg;
  }

  template<int N, typename T>
  inline Vec<N, T>::Vec(const std::initializer_list<T> args)
  {
    // NOTE: we could allow larger lists (with truncation)
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
  inline Vec<N, T>& Vec<N, T>::operator=(const Vec<N, T>& v)
  {
    data = v.data;
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator+=(const Vec<N, T>& v)
  {
    for (int i = 0; i < N; i++)
      data[i] += v.data[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator-=(const Vec<N, T>& v)
  {
    for (int i = 0; i < N; i++)
      data[i] -= v.data[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator*=(const Vec<N, T>& v)
  {
    for (int i = 0; i < N; i++)
      data[i] *= v.data[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator*=(const T& s)
  {
    for (int i = 0; i < N; i++)
      data[i] *= s;
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator/=(const Vec<N, T>& v)
  {
    for (int i = 0; i < N; i++)
      data[i] /= v.data[i];
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T>& Vec<N, T>::operator/=(const T& s)
  {
    for (int i = 0; i < N; i++)
      data[i] /= s;
    return *this;
  }

  template<int N, typename T>
  inline Vec<N, T> operator+(const Vec<N, T>& v)
  {
    return v;
  }

  template<int N, typename T>
  inline Vec<N, T> operator-(const Vec<N, T>& v)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = -v.data[i];
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator+(const Vec<N, T>& v1, const Vec<N, T>& v2)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = v1.data[i] + v2.data[i];
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator+(const Vec<N, T>& v, const T& s)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = v.data[i] + s;
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator+(const T& s, const Vec<N, T>& v)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = s + v.data[i];
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator-(const Vec<N, T>& v1, const Vec<N, T>& v2)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = v1.data[i] - v2.data[i];
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator-(const Vec<N, T>& v, const T& s)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = v.data[i] - s;
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator-(const T& s, const Vec<N, T>& v)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = s - v.data[i];
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator*(const Vec<N, T>& v1, const Vec<N, T>& v2)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = v1.data[i] * v2.data[i];
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator*(const Vec<N, T>& v, const T& s)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = v.data[i] * s;
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator*(const T& s, const Vec<N, T>& v)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = s * v.data[i];
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator/(const Vec<N, T>& v1, const Vec<N, T>& v2)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = v1.data[i] / v2.data[i];
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator/(const Vec<N, T>& v, const T& s)
  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = v.data[i] / s;
    return r;
  }

  template<int N, typename T>
  inline Vec<N, T> operator/(const T& s, const Vec<N, T>& v)

  {
    Vec<N, T> r;
    for (int i = 0; i < N; i++)
      r.data[i] = s / v.data[i];
    return r;
  }

  template<int N, typename T>
  inline bool operator==(const Vec<N, T>& v1, const Vec<N, T>& v2)
  {
    for (int i = 0; i < N; i++)
      if (v1.data[i] != v2.data[i])
        return false;
    return true;
  }

  template<int N, typename T>
  inline bool operator!=(const Vec<N, T>& v1, const Vec<N, T>& v2)
  {
    for (int i = 0; i < N; i++)
      if (v1.data[i] != v2.data[i])
        return true;
    return false;
  }

#pragma endregion
#pragma region "Vec2 Methods"
  template<typename T>
  inline Vec<2, T>::Vec(const std::initializer_list<T> args)
  {
    // NOTE: we could allow larger lists (with truncation)
    assert(args.size() <= 2);
    int ix = 0;
    for (auto it = args.begin(); it != args.end() && ix < 2; ++it)
      data.at(ix++) = *it;
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
  inline Vec<2, T>& Vec<2, T>::operator=(const Vec<2, T>& v)
  {
    data = v.data;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator+=(const Vec<2, T>& v)
  {
    x += v.x;
    y += v.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator-=(const Vec<2, T>& v)
  {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator*=(const Vec<2, T>& v)
  {
    x *= v.x;
    y *= v.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator*=(const T& s)
  {
    x *= s;
    y *= s;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator/=(const Vec<2, T>& v)
  {
    x /= v.x;
    y /= v.y;
    return *this;
  }

  template<typename T>
  inline Vec<2, T>& Vec<2, T>::operator/=(const T& s)
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
  inline Vec<3, T>& Vec<3, T>::operator=(const Vec<3, T>& v)
  {
    data = v.data;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator+=(const Vec<3, T>& v)
  {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator-=(const Vec<3, T>& v)
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator*=(const Vec<3, T>& v)
  {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator*=(const T& s)
  {
    x *= s;
    y *= s;
    z *= s;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator/=(const Vec<3, T>& v)
  {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
  }

  template<typename T>
  inline Vec<3, T>& Vec<3, T>::operator/=(const T& s)
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
  inline Vec<4, T>& Vec<4, T>::operator=(const Vec<4, T>& v)
  {
    data = v.data;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator+=(const Vec<4, T>& v)
  {
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator-=(const Vec<4, T>& v)
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator*=(const Vec<4, T>& v)
  {
    x *= v.x;
    y *= v.y;
    z *= v.z;
    w *= v.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator*=(const T& s)
  {
    x *= s;
    y *= s;
    z *= s;
    w *= s;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator/=(const Vec<4, T>& v)
  {
    x /= v.x;
    y /= v.y;
    z /= v.z;
    w /= v.w;
    return *this;
  }

  template<typename T>
  inline Vec<4, T>& Vec<4, T>::operator/=(const T& s)
  {
    x /= s;
    y /= s;
    z /= s;
    w /= s;
    return *this;
  }

#pragma endregion
}