#pragma once

#include <assert.h>

#include <array>
#include <string>
using str = std::string;

template<int N, typename T>
struct Vec
{
  std::array<T, N> values;

  Vec();
  Vec(T arg);

  template<typename... Args>
  Vec(Args... args)
  {
    static_assert(sizeof...(args) == N, "Invalid number of arguments");
    values = {{args...}};
  }

  int size() const { return N; };
  str to_string() const;

  T operator[](int i) const;
  T& operator[](int i);

  Vec& operator=(const Vec& v);
  Vec& operator+=(const Vec& v);
  Vec& operator-=(const Vec& v);
  Vec& operator*=(const Vec& v);
  Vec& operator*=(T s);
  Vec& operator/=(const Vec& v);
  Vec& operator/=(T s);
};

template<int N, typename T> Vec<N, T> operator+(const Vec<N, T>& v);
template<int N, typename T> Vec<N, T> operator-(const Vec<N, T>& v);
template<int N, typename T> Vec<N, T> operator+(const Vec<N, T>& v1, const Vec<N, T>& v2);
template<int N, typename T> Vec<N, T> operator-(const Vec<N, T>& v1, const Vec<N, T>& v2);
template<int N, typename T> Vec<N, T> operator*(const Vec<N, T>& v1, const Vec<N, T>& v2);
template<int N, typename T> Vec<N, T> operator*(const Vec<N, T>& v, T s);
template<int N, typename T> Vec<N, T> operator*(T s, const Vec<N, T>& v);
template<int N, typename T> Vec<N, T> operator/(const Vec<N, T>& v1, const Vec<N, T>& v2);
template<int N, typename T> Vec<N, T> operator/(const Vec<N, T>& v, T s);
template<int N, typename T> Vec<N, T> operator/(T s, const Vec<N, T>& v);

template<int N, typename T> bool operator==(const Vec<N, T>& v1, const Vec<N, T>& v2);
template<int N, typename T> bool operator!=(const Vec<N, T>& v1, const Vec<N, T>& v2);
template<int N, typename T> bool operator<(const Vec<N, T>& v1, const Vec<N, T>& v2);
template<int N, typename T> bool operator>(const Vec<N, T>& v1, const Vec<N, T>& v2);
template<int N, typename T> bool operator<=(const Vec<N, T>& v1, const Vec<N, T>& v2);
template<int N, typename T> bool operator>=(const Vec<N, T>& v1, const Vec<N, T>& v2);

template<typename T>
struct Vec2 : public Vec<2, T>
{
  Vec2() : Vec<2,T>() {}
  Vec2(T s) : Vec<2,T>(s) {}
  Vec2(T x, T y) : Vec<2,T>(x, y) {}

  T& x() { return Vec<2,T>::values[0]; };
  T& y() { return Vec<2,T>::values[1]; };
};

template<typename T>
struct Vec3 : public Vec<3, T>
{
  Vec3() : Vec<3,T>() {}
  Vec3(T s) : Vec<3,T>(s) {}
  Vec3(T x, T y, T z) : Vec<3,T>(x, y, z) {}

  T& x() { return Vec<3,T>::values[0]; };
  T& y() { return Vec<3,T>::values[1]; };
  T& z() { return Vec<3,T>::values[2]; };
};

template<typename T>
struct Vec4 : public Vec<4, T>
{
  Vec4() : Vec<4,T>() {}
  Vec4(T s) : Vec<4,T>(s) {}
  Vec4(T x, T y, T z, T w) : Vec<4,T>(x, y, z, w) {}

  T& x() { return Vec<4,T>::values[0]; };
  T& y() { return Vec<4,T>::values[1]; };
  T& z() { return Vec<4,T>::values[2]; };
  T& w() { return Vec<4,T>::values[3]; };
};