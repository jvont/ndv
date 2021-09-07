#pragma once

#include <ndv/vec.h>

#include <assert.h>
#include <initializer_list>

namespace ndv
{
#pragma region "Mat Definitions"

  // Matrices are stored in column-major format. However, NxM denotes N rows
  // and M columns. Essentially, matrices are constructed in row-major format,
  // but the underlying structure is column-major.
  template<int N, int M, typename T>
  struct Mat
  {
    union
    {
      Vec<N, T> col[M];
      T data[M][N];
    };

    Mat();
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<N, T> operator[](int i) const;
    Vec<N, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
  };

  template<typename T>
  struct Mat<2, 2, T>
  {
    union
    {
      Vec<2, T> col[2];
      T data[2][2];
    };

    static const Mat identity;
    static const Mat zero;

    Mat();
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<2, T> operator[](int i) const;
    Vec<2, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
  };
  using Mat2x2i = Mat<2, 2, int>;
  using Mat2x2f = Mat<2, 2, float>;
  using Mat2x2d = Mat<2, 2, double>;

  template<typename T>
  struct Mat<3, 3, T>
  {
    union
    {
      Vec<3, T> col[3];
      T data[3][3];
    };

    static const Mat identity;
    static const Mat zero;

    Mat();
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<3, T> operator[](int i) const;
    Vec<3, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
  };
  using Mat3x3i = Mat<3, 3, int>;
  using Mat3x3f = Mat<3, 3, float>;
  using Mat3x3d = Mat<3, 3, double>;

  template<typename T>
  struct Mat<4, 4, T>
  {
    union
    {
      Vec<4, T> col[4];
      T data[4][4];
    };

    static const Mat identity;
    static const Mat zero;

    Mat();
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<4, T> operator[](int i) const;
    Vec<4, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
  };
  using Mat4x4i = Mat<4, 4, int>;
  using Mat4x4f = Mat<4, 4, float>;
  using Mat4x4d = Mat<4, 4, double>;

#pragma endregion
#pragma region "Base Methods"
  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat()
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        data[c][r] = (c == r) ? T(1) : T(0);
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= N * M);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[c][r++] = *it;
      if (r >= N)
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
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= M);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
      {
        data[c++][r] = *it2;
      }
      r++;
    }
  }

  template<int N, int M, typename T>
  inline Vec<N, T> Mat<N, M, T>::operator[](int i) const
  {
    assert(i >= 0 && i < M);
    return col[i];
  }

  template<int N, int M, typename T>
  inline Vec<N, T>& Mat<N, M, T>::operator[](int i)
  {
    assert(i >= 0 && i < M);
    return col[i];
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator=(const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      data[c] = rhs[c];
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator+=(const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        data[c][r] += rhs[c][r]
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator-=(const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        data[c][r] -= rhs[c][r]
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator*=(const Mat<N, M, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator+(const Mat<N, M, T>& rhs)
  {
    return rhs;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator-(const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        result[c][r] = -rhs[c][r]
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator+(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        result[c][r] = lhs[c][r] + rhs[c][r]
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator-(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        result[c][r] = lhs[c][r] - rhs[c][r]
    return result;
  }

  template<int N, int M, int O, typename T>
  inline Mat<N, O, T> operator*(const Mat<N, M, T>& lhs, const Mat<M, O, T>& rhs)
  {
    Mat<N, O, T> result;
    for (int c = 0; c < O; c++)
    {
      for (int r = 0; r < N; r++)
      {
        T val = 0;
        for (int i = 0; i < M; i++)
          val += lhs[i][r] * rhs[c][i];
        result[c][r] = val;
      }
    }
    return result;
  }

  template<int N, int M, typename T>
  inline Vec<N, T> operator*(const Mat<N, M, T>& lhs, const Vec<M, T>& rhs)
  {
    Vec<N, T> result;
    for (int r = 0; r < N; r++)
    {
      T val = 0;
      for (int c = 0; c < M; c++)
        val += lhs[c][r] * rhs[c];
      result[r] = val;
    }
    return result;
  }

  template<int N, int M, typename T>
  inline bool operator==(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        if (lhs[c][r] != rhs[c][r])
          return false;
    return true;
  }

  template<int N, int M, typename T>
  inline bool operator!=(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    for (int c = 0; c < M; c++)
      for (int r = 0; r < N; r++)
        if (lhs[c][r] != rhs[c][r])
          return true;
    return false;
  }

#pragma endregion
#pragma region "Mat2 Methods"
  template<typename T>
  inline Mat<2, 2, T>::Mat()
  {
    for (int c = 0; c < 2; c++)
      for (int r = 0; r < 2; r++)
        data[c][r] = (c == r) ? T(1) : T(0);
  }

  template<typename T>
  inline Mat<2, 2, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 4);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[c][r++] = *it;
      if (r >= 2)
      {
        c++;
        r = 0;
      }
    }
  }
  
  template<typename T>
  inline Mat<2, 2, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= 2);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= 2);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
      {
        data[c++][r] = *it2;
      }
      r++;
    }
  }

  template<typename T> const Mat<2, 2, T> Mat<2, 2, T>::identity = Mat<2, 2, T>({{1,0},{0,1}});
  template<typename T> const Mat<2, 2, T> Mat<2, 2, T>::zero = Mat<2, 2, T>({{0,0},{0,0}});

  template<typename T>
  inline Vec<2, T> Mat<2, 2, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 2);
    return col[i];
  }

  template<typename T>
  inline Vec<2, T>& Mat<2, 2, T>::operator[](int i)
  {
    assert(i >= 0 && i < 2);
    return col[i];
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator=(const Mat<2, 2, T>& rhs)
  {
    for (int c = 0; c < 2; c++)
      data[c] = rhs[c];
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator+=(const Mat<2, 2, T>& rhs)
  {
    for (int c = 0; c < 2; c++)
      for (int r = 0; r < 2; r++)
        data[c][r] += rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator-=(const Mat<2, 2, T>& rhs)
  {
    for (int c = 0; c < 2; c++)
      for (int r = 0; r < 2; r++)
        data[c][r] -= rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator*=(const Mat<2, 2, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

#pragma endregion
#pragma region "Mat3 Methods"
  template<typename T>
  inline Mat<3, 3, T>::Mat()
  {
    for (int c = 0; c < 3; c++)
      for (int r = 0; r < 3; r++)
        data[c][r] = (c == r) ? T(1) : T(0);
  }

  template<typename T>
  inline Mat<3, 3, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 9);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[c][r++] = *it;
      if (r >= 3)
      {
        c++;
        r = 0;
      }
    }
  }
  
  template<typename T>
  inline Mat<3, 3, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= 3);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= 3);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
      {
        data[c++][r] = *it2;
      }
      r++;
    }
  }

  template<typename T> const Mat<3, 3, T> Mat<3, 3, T>::identity = Mat<3, 3, T>({{1,0,0},{0,1,0},{0,0,1}});
  template<typename T> const Mat<3, 3, T> Mat<3, 3, T>::zero = Mat<3, 3, T>({{0,0,0},{0,0,0},{0,0,0}});

  template<typename T>
  inline Vec<3, T> Mat<3, 3, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 3);
    return col[i];
  }

  template<typename T>
  inline Vec<3, T>& Mat<3, 3, T>::operator[](int i)
  {
    assert(i >= 0 && i < 3);
    return col[i];
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator=(const Mat<3, 3, T>& rhs)
  {
    for (int c = 0; c < 3; c++)
      data[c] = rhs[c];
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator+=(const Mat<3, 3, T>& rhs)
  {
    for (int c = 0; c < 3; c++)
      for (int r = 0; r < 3; r++)
        data[c][r] += rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator-=(const Mat<3, 3, T>& rhs)
  {
    for (int c = 0; c < 3; c++)
      for (int r = 0; r < 3; r++)
        data[c][r] -= rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator*=(const Mat<3, 3, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

#pragma endregion
#pragma region "Mat4 Methods"
  template<typename T>
  inline Mat<4, 4, T>::Mat()
  {
    for (int c = 0; c < 4; c++)
      for (int r = 0; r < 4; r++)
        data[c][r] = (c == r) ? T(1) : T(0);
  }

  template<typename T>
  inline Mat<4, 4, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 16);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[c][r++] = *it;
      if (r >= 4)
      {
        c++;
        r = 0;
      }
    }
  }
  
  template<typename T>
  inline Mat<4, 4, T>::Mat(const std::initializer_list<std::initializer_list<T>> args)
  {
    assert(args.size() <= 4);
    int r = 0;
    for (auto it1 = args.begin(); it1 != args.end(); ++it1)
    {
      std::initializer_list<T> args2 = *it1;
      assert(args2.size() <= 4);
      int c = 0;
      for (auto it2 = args2.begin(); it2 != args2.end(); ++it2)
      {
        data[c++][r] = *it2;
      }
      r++;
    }
  }

  template<typename T> const Mat<4, 4, T> Mat<4, 4, T>::identity = Mat<4, 4, T>({{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}});
  template<typename T> const Mat<4, 4, T> Mat<4, 4, T>::zero = Mat<4, 4, T>({{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}});

  template<typename T>
  inline Vec<4, T> Mat<4, 4, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 4);
    return col[i];
  }

  template<typename T>
  inline Vec<4, T>& Mat<4, 4, T>::operator[](int i)
  {
    assert(i >= 0 && i < 4);
    return col[i];
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator=(const Mat<4, 4, T>& rhs)
  {
    for (int c = 0; c < 4; c++)
      data[c] = rhs[c];
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator+=(const Mat<4, 4, T>& rhs)
  {
    for (int c = 0; c < 4; c++)
      for (int r = 0; r < 4; r++)
        data[c][r] += rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator-=(const Mat<4, 4, T>& rhs)
  {
    for (int c = 0; c < 4; c++)
      for (int r = 0; r < 4; r++)
        data[c][r] -= rhs[c][r]
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator*=(const Mat<4, 4, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

#pragma endregion
}