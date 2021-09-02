#pragma once

template<int N, typename T>
struct Vec
{
  T values[N];

  int size() const { return N; }

  Vec& operator+=(const Vec& v);
};

template<int N, typename T>
Vec<N, T> operator*(const Vec<N, T>& v1, const Vec<N, T>& v2);

template<int N, typename T>
Vec<N, T> operator*(const Vec<N, T>& v, float s);