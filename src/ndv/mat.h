#pragma once

#include <ndv/vec.h>

#include <assert.h>
#include <initializer_list>

namespace ndv
{
#pragma region "Mat Definitions"
  // Matrices are stored in row-major format, where NxM denotes N rows and M columns.
  template<int N, int M, typename T>
  struct Mat
  {
    union
    {
      Vec<M, T> row[N];
      T data[N][M];
    };

    static Mat diag(T diag_val);
    static Mat full(T fill_val);
    static const Mat identity;
    static const Mat zero;

    Mat() = default;
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<N, T> operator[](int i) const;
    Vec<N, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
    Mat& operator*=(T rhs);
    Mat& operator/=(T rhs);
  };

  // prevent 1-dimensional matrices
  template<int N, typename T> struct Mat<N, 1, T>;
  template<int M, typename T> struct Mat<1, M, T>;
  template<typename T> struct Mat<1, 1, T>;

  template<typename T>
  struct Mat<2, 2, T>
  {
    union
    {
      Vec<2, T> row[2];
      T data[2][2];
    };

    static Mat diag(T diag_val);
    static Mat full(T fill_val);
    static const Mat identity;
    static const Mat zero;

    Mat() = default;
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<2, T> operator[](int i) const;
    Vec<2, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
    Mat& operator*=(T rhs);
    Mat& operator/=(T rhs);
  };
  using Mat2x2i = Mat<2, 2, int>;
  using Mat2x2f = Mat<2, 2, float>;
  using Mat2x2d = Mat<2, 2, double>;

  template<typename T>
  struct Mat<3, 3, T>
  {
    union
    {
      Vec<3, T> row[3];
      T data[3][3];
    };

    static Mat diag(T diag_val);
    static Mat full(T fill_val);
    static const Mat identity;
    static const Mat zero;

    Mat() = default;
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<3, T> operator[](int i) const;
    Vec<3, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
    Mat& operator*=(T rhs);
    Mat& operator/=(T rhs);
  };
  using Mat3x3i = Mat<3, 3, int>;
  using Mat3x3f = Mat<3, 3, float>;
  using Mat3x3d = Mat<3, 3, double>;

  template<typename T>
  struct Mat<4, 4, T>
  {
    union
    {
      Vec<4, T> row[4];
      T data[4][4];
    };

    static Mat diag(T diag_val);
    static Mat full(T fill_val);
    static const Mat identity;
    static const Mat zero;

    Mat() = default;
    Mat(const std::initializer_list<T> args);
    Mat(const std::initializer_list<std::initializer_list<T>> args);

    Vec<4, T> operator[](int i) const;
    Vec<4, T>& operator[](int i);

    Mat& operator=(const Mat& rhs);
    Mat& operator+=(const Mat& rhs);
    Mat& operator-=(const Mat& rhs);
    Mat& operator*=(const Mat& rhs);
    Mat& operator*=(T rhs);
    Mat& operator/=(T rhs);
  };
  using Mat4x4i = Mat<4, 4, int>;
  using Mat4x4f = Mat<4, 4, float>;
  using Mat4x4d = Mat<4, 4, double>;

#pragma endregion
#pragma region "Base Methods"
  template<int N, int M, typename T> Mat<N, M, T> Mat<N, M, T>::diag(T diag_val)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = (r == c) ? diag_val : 0;
    return result;
  }

  template<int N, int M, typename T> Mat<N, M, T> Mat<N, M, T>::full(T fill_val)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = fill_val;
    return result;
  }

  template<int N, int M, typename T> const Mat<N, M, T> Mat<N, M, T>::identity = Mat<N, M, T>::diag(1);
  template<int N, int M, typename T> const Mat<N, M, T> Mat<N, M, T>::zero = Mat<N, M, T>::full(0);

  template<int N, int M, typename T>
  inline Mat<N, M, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= N * M);
    int r = 0, c = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[r][c++] = *it;
      if (c >= M)
      {
        r++;
        c = 0;
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
        data[r++][c] = *it2;
      r++;
    }
  }

  template<int N, int M, typename T>
  inline Vec<N, T> Mat<N, M, T>::operator[](int i) const
  {
    assert(i >= 0 && i < M);
    return row[i];
  }

  template<int N, int M, typename T>
  inline Vec<N, T>& Mat<N, M, T>::operator[](int i)
  {
    assert(i >= 0 && i < M);
    return row[i];
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator=(const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; c++)
      data[r] = rhs[r];
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator+=(const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        data[r][c] += rhs[r][c];
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator-=(const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        data[r][c] -= rhs[r][c];
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator*=(const Mat<N, M, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator*=(T rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        data[r][c] *= rhs;
    return *this;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T>& Mat<N, M, T>::operator/=(T rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        data[r][c] /= rhs;
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
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = -rhs[r][c];
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator+(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs[r][c] + rhs[r][c];
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator-(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs[r][c] - rhs[r][c];
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
        result[r][c] = val;
      }
    }
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator*(const Mat<N, M, T>& lhs, T rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs[r][c] * rhs;
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator*(T lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs * rhs[r][c];
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
        val += lhs[r][c] * rhs[c];
      result[r] = val;
    }
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator/(const Mat<N, M, T>& lhs, T rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs[r][c] / rhs;
    return result;
  }

  template<int N, int M, typename T>
  inline Mat<N, M, T> operator/(T lhs, const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = lhs / rhs[r][c];
    return result;
  }

  template<int N, int M, typename T>
  inline bool operator==(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        if (lhs[r][c] != rhs[r][c])
          return false;
    return true;
  }

  template<int N, int M, typename T>
  inline bool operator!=(const Mat<N, M, T>& lhs, const Mat<N, M, T>& rhs)
  {
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        if (lhs[r][c] != rhs[r][c])
          return true;
    return false;
  }

#pragma endregion
#pragma region "Mat2 Methods"
  template<typename T> Mat<2, 2, T> Mat<2, 2, T>::diag(T diag_val)
  {
    Mat<2, 2, T> result;
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        result[r][c] = (c == r) ? diag_val : 0;
    return result;
  }

  template<typename T> Mat<2, 2, T> Mat<2, 2, T>::full(T fill_val)
  {
    Mat<2, 2, T> result;
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        result[r][c] = fill_val;
    return result;
  }

  template<typename T> const Mat<2, 2, T> Mat<2, 2, T>::identity = Mat<2, 2, T>::diag(1);
  template<typename T> const Mat<2, 2, T> Mat<2, 2, T>::zero = Mat<2, 2, T>::full(0);

  template<typename T>
  inline Mat<2, 2, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 4);
    int r = 0, c = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[r][c++] = *it;
      if (c >= 2)
      {
        r++;
        c = 0;
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
        data[r][c++] = *it2;
      r++;
    }
  }

  template<typename T>
  inline Vec<2, T> Mat<2, 2, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 2);
    return row[i];
  }

  template<typename T>
  inline Vec<2, T>& Mat<2, 2, T>::operator[](int i)
  {
    assert(i >= 0 && i < 2);
    return row[i];
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator=(const Mat<2, 2, T>& rhs)
  {
    for (int r = 0; r < 2; r++)
      data[r] = rhs[r];
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator+=(const Mat<2, 2, T>& rhs)
  {
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        data[r][c] += rhs[r][c]
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator-=(const Mat<2, 2, T>& rhs)
  {
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        data[r][c] -= rhs[r][c]
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator*=(const Mat<2, 2, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator*=(T rhs)
  {
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        data[r][c] *= rhs;
    return *this;
  }

  template<typename T>
  inline Mat<2, 2, T>& Mat<2, 2, T>::operator/=(T rhs)
  {
    for (int r = 0; r < 2; r++)
      for (int c = 0; c < 2; c++)
        data[r][c] /= rhs;
    return *this;
  }

#pragma endregion
#pragma region "Mat3 Methods"
  template<typename T> Mat<3, 3, T> Mat<3, 3, T>::diag(T diag_val)
  {
    Mat<3, 3, T> result;
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        result[r][c] = (c == r) ? diag_val : 0;
    return result;
  }

  template<typename T> Mat<3, 3, T> Mat<3, 3, T>::full(T fill_val)
  {
    Mat<3, 3, T> result;
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        result[r][c] = fill_val;
    return result;
  }

  template<typename T> const Mat<3, 3, T> Mat<3, 3, T>::identity = Mat<3, 3, T>::diag(1);
  template<typename T> const Mat<3, 3, T> Mat<3, 3, T>::zero = Mat<3, 3, T>::full(0);

  template<typename T>
  inline Mat<3, 3, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 9);
    int r = 0, c = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[r][c++] = *it;
      if (c >= 3)
      {
        r++;
        c = 0;
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
        data[r][c++] = *it2;
      r++;
    }
  }

  template<typename T>
  inline Vec<3, T> Mat<3, 3, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 3);
    return row[i];
  }

  template<typename T>
  inline Vec<3, T>& Mat<3, 3, T>::operator[](int i)
  {
    assert(i >= 0 && i < 3);
    return row[i];
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator=(const Mat<3, 3, T>& rhs)
  {
    for (int r = 0; r < 3; r++)
      data[r] = rhs[r];
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator+=(const Mat<3, 3, T>& rhs)
  {
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        data[r][c] += rhs[r][c]
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator-=(const Mat<3, 3, T>& rhs)
  {
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        data[r][c] -= rhs[r][c]
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator*=(const Mat<3, 3, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator*=(T rhs)
  {
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        data[r][c] *= rhs;
    return *this;
  }

  template<typename T>
  inline Mat<3, 3, T>& Mat<3, 3, T>::operator/=(T rhs)
  {
    for (int r = 0; r < 3; r++)
      for (int c = 0; c < 3; c++)
        data[r][c] /= rhs;
    return *this;
  }

#pragma endregion
#pragma region "Mat4 Methods"
  template<typename T> Mat<4, 4, T> Mat<4, 4, T>::diag(T diag_val)
  {
    Mat<4, 4, T> result;
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        result[r][c] = (c == r) ? diag_val : 0;
    return result;
  }

  template<typename T> Mat<4, 4, T> Mat<4, 4, T>::full(T fill_val)
  {
    Mat<4, 4, T> result;
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        result[r][c] = fill_val;
    return result;
  }
  
  template<typename T> const Mat<4, 4, T> Mat<4, 4, T>::identity = Mat<4, 4, T>::diag(1);
  template<typename T> const Mat<4, 4, T> Mat<4, 4, T>::zero = Mat<4, 4, T>::full(0);

  template<typename T>
  inline Mat<4, 4, T>::Mat(const std::initializer_list<T> args)
  {
    assert(args.size() <= 16);
    int c = 0, r = 0;
    for (auto it = args.begin(); it != args.end(); ++it)
    {
      data[r][c++] = *it;
      if (c >= 4)
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
        data[r][c++] = *it2;
      r++;
    }
  }

  template<typename T>
  inline Vec<4, T> Mat<4, 4, T>::operator[](int i) const
  {
    assert(i >= 0 && i < 4);
    return row[i];
  }

  template<typename T>
  inline Vec<4, T>& Mat<4, 4, T>::operator[](int i)
  {
    assert(i >= 0 && i < 4);
    return row[i];
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator=(const Mat<4, 4, T>& rhs)
  {
    for (int r = 0; r < 4; r++)
      data[r] = rhs[r];
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator+=(const Mat<4, 4, T>& rhs)
  {
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        data[r][c] += rhs[r][c]
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator-=(const Mat<4, 4, T>& rhs)
  {
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        data[r][c] -= rhs[r][c]
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator*=(const Mat<4, 4, T>& rhs)
  {
    *this = *this * rhs;
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator*=(T rhs)
  {
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        data[r][c] *= rhs;
    return *this;
  }

  template<typename T>
  inline Mat<4, 4, T>& Mat<4, 4, T>::operator/=(T rhs)
  {
    for (int r = 0; r < 4; r++)
      for (int c = 0; c < 4; c++)
        data[r][c] /= rhs;
    return *this;
  }

#pragma endregion
#pragma region "Utility Methods"
  template<int N, int M, typename T>
  inline Mat<N, M, T> transpose(const Mat<N, M, T>& rhs)
  {
    Mat<N, M, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < M; c++)
        result[r][c] = rhs[c][r];
    return result;
  }

  // returns the submatrix obtained by removing row, col
  template<int N, typename T>
  inline Mat<N-1, N-1, T> submatrix(const Mat<N, N, T>& rhs, int row, int col)
  {
    assert(row >= 0 && row < N);
    assert(col >= 0 && col < N);

    Mat<N-1, N-1, T> result;
    int i = 0, j = 0;
    for (int r = 0; r < N; r++)
    {
      for (int c = 0; c < N; c++)
      {
        if (r != row && c != col)
          result[i][j++] = rhs[r][c];
        
        if (j == N - 1)
        {
          j = 0;
          i++;
        }
      }
    }
    return result;
  }

  template<typename T>
  inline Mat<2, 2, T> cofactor(const Mat<2, 2, T>& rhs)
  {
    return Mat<2, 2, T>({
      {rhs[1][1], -rhs[0][1]},
      {-rhs[1][0], rhs[0][0]}
    });
  }

  template<int N, typename T>
  inline Mat<N, N, T> cofactor(const Mat<N, N, T>& rhs)
  {
    Mat<N, N, T> result;
    for (int r = 0; r < N; r++)
      for (int c = 0; c < N; c++)
        result[r][c] = (1 - 2 * ((r + c) % 2)) * determinant(submatrix(rhs, r, c));
    return result;
  }

  template<int N, typename T>
  inline Mat<N, N, T> adjoint(const Mat<N, N, T>& rhs)
  {
    return transpose(cofactor(rhs));
  }

  template<typename T>
  inline T determinant(const Mat<2, 2, T>& rhs)
  {
    return (rhs[0][0] * rhs[1][1] - rhs[0][1] * rhs[1][0]);
  }

  template<typename T>
  inline T determinant(const Mat<3, 3, T>& rhs)
  {
    return (
      rhs[0][0] * (rhs[1][1] * rhs[2][2] - rhs[2][1] * rhs[1][2]) -
      rhs[1][0] * (rhs[0][1] * rhs[2][2] - rhs[2][1] * rhs[0][2]) +
      rhs[2][0] * (rhs[0][1] * rhs[1][2] - rhs[1][1] * rhs[0][2])
    );
  }

  // generic determinant method (slow). currently gets called for 4x4 matrices
  template<int N, typename T>
  inline T determinant(const Mat<N, N, T>& rhs)
  {
    T result = 0;
    for (int c = 0; c < N; c++)
      result += (1 - 2 * (c % 2)) * rhs[0][c] * determinant(submatrix(rhs, 0, c));
    return result;
  }

  template<int N, typename T>
  inline Mat<N, N, T> inverse(const Mat<N, N, T>& rhs)
  {
    T det = determinant(rhs);
    // if (approx_equal(det, T(0.0f)))
    if (det == 0)
      return Mat<N, N, T>::zero;

    return (adjoint(rhs) / determinant(rhs));
  }

  template<int N, typename T>
  inline Mat<N, N, T> scale(Mat<N, N, T>& result, const Vec<N, T>& scaling)
  {
    for (int r = 0; r < N; r++)
      result[r] *= scaling[r];
    return result;
  }

  template<int N, typename T>
  inline Mat<N, N, T> scale(const Vec<N, T>& scaling)
  {
    Mat<N, N, T> result = Mat<N, N, T>::identity;
    scale(&result, scaling);
    return result;
  }

  template<int N, typename T>
  inline Mat<N, N, T> scale_affine(Mat<N, N, T>& result, const Vec<N-1, T>& scaling)
  {
    for (int i = 0; i < N-1; i++)
      result[i][i] *= scaling[i];
    return result;
  }

  template<int N, typename T>
  inline Mat<N, N, T> scale_affine(const Vec<N-1, T>& scale)
  {
    Mat<N, N, T> result = Mat<N, N, T>::identity;
    scale(&result, scale);
    return result;
  }

  // template<typename T>
  // inline Mat<2, 2, T> rotate(Mat<2, 2, T>& result, T angle)
  // {
  //   T c = cos(angle);
  //   T s = sin(angle);
  //   return Mat<2, 2, T>({
  //     {c, -s},
  //     {s, c}
  //   });
  // }

  // template<typename T>
  // inline Mat<2, 2, T> rotate(T angle)
  // {
  //   
  // }

  // template<typename T>
  // inline Mat<3, 3, T> rotate_affine(Mat<3, 3, T>& result, T angle)
  // {
  //   T c = cos(angle);
  //   T s = sin(angle);

  //   Mat<3, 3, T> result;
  //   result[0] = c * m[0] + s * m[1];
  //   result[1] = -s * m[0] + c * m[1];
  //   result[2] = m[2];
  //   return result;
  // }

  // template<typename T>
  // inline Mat<3, 3, T> rotate_affine(T angle)
  // {
  //   return rotate(angle, Mat<3, 3, T>::identity);
  // }

  // nice implmenetation from: https://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/index.htm
  template<typename T>
  inline Mat<3, 3, T> rotate(const Vec<3, T>& axis, T angle)
  {
    T c = cos(angle);
    T s = sin(angle);

    Vec<3, T> ax = normalize(axis);
    Vec<3, T> axinv = ((T(1.0f) - c) * ax);

    Mat<3, 3, T> result;
    result[0][0] = axinv.x * ax.x + c;
    result[1][0] = axinv.x * ax.y + s * ax.z;
    result[2][0] = axinv.x * ax.z - s * ax.y;

    result[0][1] = axinv.y * ax.x - s * ax.z;
    result[1][1] = axinv.y * ax.y + c;
    result[2][1] = axinv.y * ax.z + s * ax.x;

    result[0][2] = axinv.z * ax.x + s * ax.y;
    result[1][2] = axinv.z * ax.y - s * ax.x;
    result[2][2] = axinv.z * ax.z + c;
    return result;
  }

  // template<typename T>
  // inline Mat<3, 3, T> rotate(Mat<3, 3, T>& result, const Vec<3, T>& axis, T angle)
  // {
    
  // }

  // template<typename T>
  // inline Mat<4, 4, T> rotate_affine(Vec<3, T> axis, T angle)
  // {
  //   Mat<3, 3, T> r = rotate(axis, angle);
  //   Mat<4, 4, T> result;
  //   for (int r = 0; r < 3; r++)
  //     for (int c = 0; c < 3; r++)
  //       result[r][c] = r[r][c];
  //   return result;
  // }

  // template<typename T>
  // inline Mat<4, 4, T> rotate_affine(Mat<4, 4, T>& result, Vec<3, T> axis, T angle)
  // {

  // }

  // template<typename T>
  // inline Mat<3, 3, T> translate(Vec<2, T> distance, const Mat<3, 3, T>& m = Mat<3, 3, T>::identity)
  // {
  //   Mat<3, 3, T> result = m;
  //   result[2] = m[0] * distance[0] + m[1] * distance[1] + m[2];
  //   return result;
  // }

  // template<typename T>
  // inline Mat<4, 4, T> translate(Vec<3, T> distance, const Mat<4, 4, T>& m = Mat<4, 4, T>::identity)
  // {
  //   Mat<4, 4, T> result = m;
  //   result[3] = m[0] * distance[0] + m[1] * distance[1] + m[2] * distance[2] + m[3];
  //   return result;
  // }

  // template<typename T>
  // inline Mat<4, 4, T> look_at(const Vec<3, float>& eye, const Vec<3, float>& target, const Vec<3, float>& up)
  // {

  // }

  // template<typename T>
  // inline Mat<4, 4, T> orthographic(T left, T right, T top, T bottom, T near, T far)
  // {
  //   T m00 = 2.0f / (right - left);
  //   T m11 = 2.0f / (top - bottom);
  //   T m30 = -(right + left) / (right - left);
  //   T m31 = -(top + bottom) / (top - bottom);
  //   T m32 = -(far + near) / (far - near);

  //   return Mat<4, 4, T>({
  //     {m00, 0,   0,   0},
  //     {0,   m11, 0,   0},
  //     {0,   0,   0,   0},
  //     {m30, m31, m32, 1}
  //   });
  // }

  // template<typename T>
  // inline Mat<4, 4, T> orthographic(T width, T height, T near, T far)
  // {
  //   T right = 0.5f * width;
  //   T top = 0.5f * height;

  //   T m00 = 1.0f / right;
  //   T m11 = 1.0f / top;
  //   T m22 = -2.0f / far - near;
  //   T m32 = -(far + near) / (far - near);

  //   return Mat<4, 4, T>({
  //     {m00, 0,   0,   0},
  //     {0,   m11, 0,   0},
  //     {0,   0,   m22, 0},
  //     {0,   0,   m32, 1}
  //   });
  // }

  // Mat4 perspective(T left, T right, T top, T bottom, T near, T far)
  // {
  //   T m00 = 2.0f * near / (right - left);
  //   T m11 = 2.0f * near / (top - bottom);
  //   T m20 = (right + left) / (right - left);
  //   T m21 = (top + bottom) / (top - bottom);
  //   T m22 = -(far + near) / (far - near);
  //   T m23 = -1.0f;
  //   T m32 = -2.0f * far * near / (far - near);

  //   return Mat4{{
  //     {m00, 0,   0,   0  },
  //     {0,   m11, 0,   0  },
  //     {m20, m21, m22, m23},
  //     {0,   0,   m32, 1  }
  //   }};
  // }

  // Mat4 perspective(T fov_y, T aspect, T near, T far)
  // {
  //   const T tan_fov_y2 = tan(fov_y / 2.0f);

  //   T m00 = 1.0f / (aspect * tan_fov_y2);
  //   T m11 = 1.0f / tan_fov_y2;
  //   T m22 = far / (near - far);
  //   T m23 = -1.0f;
  //   T m32 = -far * near / (far - near);

  //   return Mat4{{
  //     {m00, 0,   0,   0  },
  //     {0,   m11, 0,   0  },
  //     {0,   0,   m22, m23},
  //     {0,   0,   m32, 1  }
  //   }};
  // }

  template<typename T>
  inline bool check_affine(const Mat<3, 3, T>& rhs)
  {
    return (data[0][2] == 0 && data[1][2] == 0 && data[2][2] == 1);
  }

  template<typename T>
  inline bool check_affine(const Mat<4, 4, T>& rhs)
  {
    return (data[0][3] == 0 && data[1][3] == 0 && data[2][3] == 0 && data[3][3] == 1);
  }

#pragma endregion
}