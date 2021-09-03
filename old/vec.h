#pragma once

#include <assert.h>
#include <cstdarg>

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

#include "vec.inl"