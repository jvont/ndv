#pragma once

#include <ndv/vec.h>

#include <assert.h>
#include <cstdarg>

#include <array>

namespace bones
{
#pragma region "Mat Definitions"
  template<int N, int M, typename T>
  struct Mat
  {
    union
    {
      Vec<M, T> col[N];
      T data[N][M];
    };

    Mat();
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<N, T> operator[](int i) const;
    Vec<N, T>& operator[](int i);

    // Mat& operator=(const Mat& m);
    // Mat& operator+=(const Mat& m);
    // Mat& operator+=(const T& s);
    // Mat& operator-=(const Mat& m);
    // Mat& operator-=(const T& s);
    // Mat& operator*=(const Mat& m);
    // Mat& operator*=(const T& s);
    // Mat& operator/=(const T& s);

    // template<int M> operator*=(const Vec<M, T> v); 
    // template<int M> operator/=(const Vec<M, T> v); 
  };

#pragma endregion
#pragma region "Base Methods"
  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat()
  {
    for (int i = 0; i < N; i++)
      for (int j = 0; j < M; j++)
        data[i][j] = (i == j) ? T(1) : T(0);
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= N * M);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[c][r++] = *it;
      if (r >= M)
      {
        c++;
        r = 0;
      }
    }
  }
  
  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= N);
    int c = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= M);
      int r = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
      {
        data[c][r++] = *it2;
      }
      c++;
    }
  }

  template<int N, int M, typename T>
  inline Vec<N, T> Mat<N, M, T>::operator[](int i) const
  {
    assert(i >= 0 && i < N);
    return col[i];
  }

  template<int N, int M, typename T>
  inline Vec<N, T>& Mat<N, M, T>::operator[](int i)
  {
    assert(i >= 0 && i < N);
    return col[i];
  }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T>& Mat<N, M, T>::operator=(const Mat<N, M, T>& m)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T>& Mat<N, M, T>::operator+=(const Mat<N, M, T>& m)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T>& Mat<N, M, T>::operator+=(const T& s)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T>& Mat<N, M, T>::operator-=(const Mat<N, M, T>& m)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T>& Mat<N, M, T>::operator-=(const T& s)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T>& Mat<N, M, T>::operator*=(const Mat<N, M, T>& m)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T>& Mat<N, M, T>::operator*=(const T& s)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T>& Mat<N, M, T>::operator/=(const T& s)
  // {

  // }

  // template<int M> operator*=(const Vec<M, T> v); 
  // template<int M> operator/=(const Vec<M, T> v);

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator+(const Mat<N, M, T>& m)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator-(const Mat<N, M, T>& m)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator+(const Mat<N, M, T>& m1, const Mat<N, M, T>& m2)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator+(const Mat<N, M, T>& m, const T& s)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator+(const T& s, const Mat<N, M, T>& m)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator-(const Mat<N, M, T>& m1, const Mat<N, M, T>& m2)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator-(const Mat<N, M, T>& m, const T& s)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator-(const T& s, const Mat<N, M, T>& m)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator*(const Mat<N, M, T>& m1, const Mat<N, M, T>& m2)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator*(const Mat<N, M, T>& m, const T& s)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator*(const T& s, const Mat<N, M, T>& m)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator/(const Mat<N, M, T>& m, const T& s)
  // {

  // }

  // template<int N, int M, typename T>
  // inline Mat<N, M, T> operator/(const T& s, const Mat<N, M, T>& m)
  // {

  // }


  // template<int N, int M, typename T>
  // inline bool operator==(const Mat<N, M, T>& m1, const Mat<N, M, T>& m2)
  // {

  // }

  // template<int N, int M, typename T>
  // inline bool operator!=(const Mat<N, M, T>& m1, const Mat<N, M, T>& m2)
  // {

  // }

  // Vec2 operator*(const Mat<N, M, T>& m, const Vec2& v);
#pragma endregion
#pragma region "Mat2 Methods"

#pragma endregion
#pragma region "Mat3 Methods"

#pragma endregion
#pragma region "Mat4 Methods"

#pragma endregion
}